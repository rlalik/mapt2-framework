from libcpp cimport bool
from libcpp.string cimport string

from mgeanttrack cimport _MGeantTrack, MGeantTrack
from mgeantfibersraw cimport _MGeantFibersRaw, MGeantFibersRaw
from mfiberscalsim cimport _MFibersCalSim, MFibersCalSim
from mfiberscal cimport _MFibersCal, MFibersCal

cdef extern from "MAPT.h":
    cdef cppclass _MAPT "MAPT":
        _MAPT() except +

        void initAnalysis(string, int)
        long getEventsNumber()
        int getEvent(long)
        #void printEvent()

        int getGeantTrackNum()
        int getGeantFibersRawNum()
        int getFibersCalSimNum()
        int getFibersCalNum()

        _MGeantTrack * getGeantTrack(int)
        _MGeantFibersRaw * getGeantFibersRaw(int)
        _MFibersCalSim * getFibersCalSim(int)
        _MFibersCal * getFibersCal(int)

cdef class MAPT:
    cdef _MAPT c_obj      # hold a C++ instance which we're wrapping
    def __cinit__(self,):
        self.c_obj = _MAPT()

    def initAnalysis(self, file, events):
        self.c_obj.initAnalysis(file, events)

    def getEventsNumber(self):
        return self.c_obj.getEventsNumber()

    def getEvent(self, i):
        return self.c_obj.getEvent(i)

    #def printEvent(self):
        #self.c_obj.printEvent()

    def getGeantTrackNum(self):
        return self.c_obj.getGeantTrackNum()
    def getGeantFibersRawNum(self):
        return self.c_obj.getGeantFibersRawNum()
    def getFibersCalSimNum(self):
        return self.c_obj.getFibersCalSimNum()
    def getFibersCalNum(self):
        return self.c_obj.getFibersCalNum()

    def getGeantTrack(self, i):
        _mgt = self.c_obj.getGeantTrack(i)
        cdef mgt = MGeantTrack.create(_mgt)
        return mgt

    def getGeantFibersRaw(self, i):
        _mgfr = self.c_obj.getGeantFibersRaw(i)
        cdef mgfr = MGeantFibersRaw.create(_mgfr)
        return mgfr

    def getFibersCalSim(self, i):
        _mfcs = self.c_obj.getFibersCalSim(i)
        cdef mfcs = MFibersCalSim.create(_mfcs)
        return mfcs

    def getFibersCal(self, i):
        _mfc = self.c_obj.getFibersCal(i)
        cdef mfc = MFibersCal.create(_mfc)
        return mfc
