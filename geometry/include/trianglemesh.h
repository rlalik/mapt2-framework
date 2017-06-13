#ifndef TRIANGLEMESH_H_
#define TRIANGLEMESH_H_

#include <vector>
#include <set>
#include <list>
#include <string>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_triangle_primitive.h>


#include "TVector3.h"


typedef CGAL::Simple_cartesian<double> CKernel; ///< Geometric Kernel used for CGAL types
typedef CKernel::Segment_3 CSegment; ///< CGAL segment type
typedef CKernel::Point_3 CPoint; ///< CGAL point type
typedef CKernel::Triangle_3 CTriangle; ///< CGAL triangle type
typedef CKernel::Vector_3 CVector; ///< CGAL vector type


/**
 * Triangle class.
 *
 * Contains a CGAL triangle and an ID to identify its properties (material, solid, etc...)
 */
struct TTriangle {
	CTriangle tri; ///< CGAL triangle
	int sldindex; ///< index of corresponding solid

	/**
	 * Constructor.
	 *
	 * Create CGAL triangle and assign ID. Vertices are assumed to be in right-hand-rule order.
	 *
	 * @param pa First triangle vertex
	 * @param pb Second triangle vertex
	 * @param pc Third triangle vertex
	 * @param asldindex Index of the solid to which the triangle belongs
	 */
	TTriangle(CPoint pa, CPoint pb, CPoint pc, int asldindex): tri(CTriangle(pa, pb, pc)), sldindex(asldindex) {}

	/**
	 * Get normalized orthogonal vector.
	 *
	 * @return Normalized orthogonal vector.
	 */
	CVector normal() const{
		CVector n = tri.supporting_plane().orthogonal_vector();
		return n/sqrt(n.squared_length());
	}

	/**
	 * Get triangle area.
	 *
	 * @return Triangle area.
	 */
	double area() const{
		return sqrt(tri.squared_area());
	}
};

/**
 * Iterator to triangle list. This is stored in the AABB tree.
 */
typedef std::vector<TTriangle>::const_iterator CIterator;

/**
 * The following primitive provides the conversion facilities between
 * TTriangle and the types needed by CGAL AABB_tree
 */
struct CPrimitive {
public:
	typedef CIterator Id; ///< Type returned by CPrimitive::id().
	typedef CPoint Point; ///< Type returned by CPrimitive::reference_point().
	typedef CTriangle Datum; ///< Type returned by CPrimitive::datum().
private:
	Id m_pt; ///< this is what the AABB tree stores internally
public:
	/**
	 * Needed default constructor
	 */
	CPrimitive(): m_pt(NULL) {}

	/**
	 * Constructor
	 *
	 * this constructor is the one that receives the iterators from the
	 * iterator range given as input to the AABB_tree
	 */
	CPrimitive(CIterator it): m_pt(it) {}

	/**
	 * Return internal iterator.
	 */
	const Id& id() const { return m_pt; }

	/**
	 * Return the CGAL Primitive
	 */
	Datum datum() const
	{
		return m_pt->tri;
	}
	/**
	 * Return a reference point.
	 *
	 * returns a reference point which must be on the primitive
	 */
	Point reference_point() const{
		return m_pt->tri.vertex(0);
	}
};

typedef CGAL::AABB_traits<CKernel, CPrimitive> CTraits; ///< CGAL triangle traits type
typedef CGAL::AABB_tree<CTraits> CTree; ///< CGAL AABB tree type containing CPrimitives
#if CGAL_VERSION_NR<1040301000
	typedef boost::optional< CTree::Object_and_primitive_id > CIntersection; ///< CGAL 4.2 or older segment-triangle intersection type
#else
	typedef boost::optional< CTree::Intersection_and_primitive_id<CSegment>::Type > CIntersection; ///< CGAL 4.3 segment-triangle intersection type
#endif


/**
 * Structure that is returned by KDTree::Collision.
 */
struct TCollision{
	double s; ///< parametric coordinate of intersection point (P = p1 + s*(p2 - p1))
	double normal[3]; ///< normal (length = 1) of intersected surface
	int sldindex; ///< index of solid to which the intersected surface belongs
	double distnormal; ///< distance between start- and endpoint of colliding segment, projected onto normal direction

	/**
	 * Overloaded operator, needed for sorting
	 */
	inline bool operator < (const TCollision c) const {
		if (s == c.s)
			return sldindex > c.sldindex;
		else
			return s < c.s;
	};
};


 //! \brief Structure that is returned by KDTree::Collision.
 /*!

 */
struct TCollision2{
	double s; ///< parametric coordinate of intersection point (P = p1 + s*(p2 - p1))
	int sldindex; ///< index of solid to which the intersected surface belongs
	bool entry;
	CPoint point; ///< intersection point
	/*!
   	Overloaded operator, needed for sorting
    */
	inline bool operator < (const TCollision2 c) const {
		if (std::abs(s-c.s) <= 0.0001)
			return !entry;
		else
			return s < c.s;
	};
};

 //! \brief Class to hold your STL geometry and do intersection tests.
 /*!

 */
class TTriangleMesh {
    public:
        std::vector<TTriangle> triangles; ///< list of triangles
        CTree tree; ///< AABB tree

        /**
         * \brief Read STL-file.
         *
         * @param filename Filename of STL file
         * @param sldindex Index of solid properties assigned to this STL file
         * @param name Returns name of file
         */
        void ReadFile(const char *filename, int sldindex, char name[80] = NULL);
        void Init(); ///< create AABB tree

        /**
         * \brief Test line segment p1->p2 for collision with all triangles in previously read files.
         *
         * @param p1 Line start point
         * @param p2 Line end point
         * @param colls Found collisions are added to this list
         *
         * @return Returns true if at least one collision was found
         */
        bool Collision(const double p1[3], const double p2[3], std::set<TCollision> &colls);


		/**
		 * \brief new collison function -> finding next intersection point (not used).
		 */
		 int nextIntersection  (TVector3 startPoint, TVector3 direction, TVector3 &newPIn, TVector3 &newPOut, int &volumeIndex);

		 //! \brief Finds the next volume, identfies it, and calculates the intersection points.
	     /*!
	       Key function to find the next step through a volume. Starting from pIn
	       the function tries to find the next volume in direction dir.

	       The function returns a 0 if no further volume is found in that
	       direction (-> left world).

	       If the next volume is found the function returns a 1. newPIn is the new entry
	       point, newPOut is the new exit point, and volumeIndex_ is the volume index
	       of the traversed volume.

	       The function return -1 if an error occurs during calculation.
	     */
		 int nextIntersection2 (TVector3 startPoint, TVector3 direction, TVector3 &newPIn, TVector3 &newPOut, int &volumeIndex);

		 //! \brief Returns the next entry and output points as TVector3 (not used).
		 int nextIntersection3 (TVector3 startPoint, TVector3 direction, TVector3 &newPIn, TVector3 &newPOut, int &volumeIndex);

};

#endif // TRIANGLEMESH_H_
