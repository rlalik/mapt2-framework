cdef class MGeantTrack:
    def __cinit__(self,):
        pass

    def __dealloc__(self):
        del self.c_obj

    cpdef _print(self):
        self.c_obj._print()

    @staticmethod
    cdef MGeantTrack create(_MGeantTrack * ptr):
        cdef MGeantTrack res = MGeantTrack()
        res.c_obj = ptr
        return res
