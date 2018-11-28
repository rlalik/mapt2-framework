from libcpp cimport bool
from libcpp.string cimport string

cdef extern from "../lib/geant/MGeantTrack.h":
    cdef cppclass _MGeantTrack "MGeantTrack":
        _MGeantTrack() except +

        void _print "print"()

cdef class MGeantTrack:
    cdef _MGeantTrack * c_obj      # hold a C++ instance which we're wrapping
    cpdef _print(self)

    @staticmethod
    cdef MGeantTrack create(_MGeantTrack * ptr)
