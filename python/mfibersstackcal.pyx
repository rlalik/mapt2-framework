cdef class MFibersCal:
    def __cinit__(self,):
        pass

    def __dealloc__(self):
        del self.c_obj

    cpdef setAddress(self, m, l, f):
        self.c_obj.setAddress(m, l, f)
    cpdef getAddress(self):
        cdef int m, l, f
        self.c_obj.getAddress(m, l, f)
        return m, l, f

    cpdef setU(self, u):
        self.c_obj.setU(u)
    cpdef getU(self):
        return self.c_obj.getU()

    cpdef setY(self, y):
        self.c_obj.setY(y)
    cpdef getY(self):
        return self.c_obj.getY()

    cpdef setEnergyDeposition(self, e):
        self.c_obj.setEnergyDeposition(e)
    cpdef addEnergyDeposition(self, e):
        self.c_obj.addEnergyDeposition(e)
    cpdef getEnergyDeposition(self):
        return self.c_obj.getEnergyDeposition()

    cpdef _print(self):
        self.c_obj._print()

    @staticmethod
    cdef MFibersCal create(_MFibersCal * ptr):
        cdef MFibersCal res = MFibersCal()
        res.c_obj = ptr
        return res
