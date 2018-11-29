cdef class MGeantFibersRaw:
    def __cinit__(self,):
        pass

    def __dealloc__(self):
        del self.c_obj

    cpdef setEnergyLoss(self, e):
        self.c_obj.setEnergyLoss(e)
    cpdef addEnergyLoss(self, e):
        self.c_obj.addEnergyLoss(e)
    cpdef getEnergyLoss(self):
        return self.c_obj.getEnergyLoss()

    cpdef setEnergyDeposition(self, e):
        self.c_obj.setEnergyDeposition(e)
    cpdef addEnergyDeposition(self, e):
        self.c_obj.addEnergyDeposition(e)
    cpdef getEnergyDeposition(self):
        return self.c_obj.getEnergyDeposition()

    cpdef setEnergyQuenching(self, e):
        self.c_obj.setEnergyQuenching(e)

    cpdef setPhotons(self, p):
        self.c_obj.setPhotons(p)

    cpdef setTotalEnergy(self, e):
        self.c_obj.setTotalEnergy(e)
    cpdef getTotalEnergy(self):
        return self.c_obj.getTotalEnergy()

    cpdef setKineticEnergy(self, e):
        self.c_obj.setKineticEnergy(e)
    cpdef getKineticEnergy(self):
        return self.c_obj.getKineticEnergy()

    cpdef _print(self):
        self.c_obj._print()

    @staticmethod
    cdef MGeantFibersRaw create(_MGeantFibersRaw * ptr):
        cdef MGeantFibersRaw res = MGeantFibersRaw()
        res.c_obj = ptr
        return res
