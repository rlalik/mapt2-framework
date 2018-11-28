from libcpp cimport bool
from libcpp.string cimport string

cdef extern from "../lib/geant/MGeantFibersRaw.h":
    cdef cppclass _MGeantFibersRaw "MGeantFibersRaw":
        _MGeantFibersRaw() except +

        void setEnergyLoss(double)
        void addEnergyLoss(double)
        double getEnergyLoss()

        void setEnergyDeposition(double)
        void addEnergyDeposition(double)
        double getEnergyDeposition()

        void setEnergyQuenching(double)

        void setPhotons(int photon)
        void setTotalEnergy(double e)
        double getTotalEnergy()
        void setKineticEnergy(double e)
        double getKineticEnergy()

        void setX(int)
        void setY(int)

        int getX()
        int getY()

        void _print "print"()

cdef class MGeantFibersRaw:
    cdef _MGeantFibersRaw * c_obj      # hold a C++ instance which we're wrapping

    cpdef setEnergyLoss(self, e)
    cpdef addEnergyLoss(self, e)
    cpdef getEnergyLoss(self)

    cpdef setEnergyDeposition(self, e)
    cpdef addEnergyDeposition(self, e)
    cpdef getEnergyDeposition(self)

    cpdef setEnergyQuenching(self, e)

    cpdef setPhotons(self, p)
    cpdef setTotalEnergy(self, e)
    cpdef getTotalEnergy(self)

    cpdef setKineticEnergy(self, e)
    cpdef getKineticEnergy(self)

    cpdef setX(self, x)
    cpdef getX(self)

    cpdef setY(self, y)
    cpdef getY(self)

    cpdef _print(self)

    @staticmethod
    cdef MGeantFibersRaw create(_MGeantFibersRaw * ptr)
