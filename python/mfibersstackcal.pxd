from libcpp cimport bool
from libcpp.string cimport string

cdef extern from "../lib/fibers_stack/MFibersStackCal.h":
    cdef cppclass _MFibersStackCal "MFibersStackCal":
        _MFibersStackCal() except +

        void setAddress(int, int, int)
        void getAddress(int &, int &, int &)

        void setU(float)
        void setY(float)
        void setEnergyDeposition(float)
        void addEnergyDeposition(float)

        float getU()
        float getY()
        float getEnergyDeposition()
        
        void _print "print"()

cdef class MFibersStackCal:
    cdef _MFibersStackCal * c_obj      # hold a C++ instance which we're wrapping

    cpdef setAddress(self, m, l, f)
    cpdef getAddress(self)

    cpdef setU(self, u)
    cpdef getU(self)

    cpdef setY(self, y)
    cpdef getY(self)

    cpdef setEnergyDeposition(self, e)
    cpdef addEnergyDeposition(self, e)
    cpdef getEnergyDeposition(self)

    cpdef _print(self)

    @staticmethod
    cdef MFibersStackCal create(_MFibersStackCal * ptr)
