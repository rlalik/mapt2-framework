from libcpp cimport bool
from libcpp.string cimport string

from mgeanttrack cimport _MGeantTrack, MGeantTrack
from mgeantfibersraw cimport _MGeantFibersRaw, MGeantFibersRaw
from mfibersstackcalsim cimport _MFibersStackCalSim, MFibersStackCalSim
from mfibersstackcal cimport _MFibersStackCal, MFibersStackCal

cdef extern from "MAPT.h":
    cdef cppclass _MAPT "MAPT":
        _MAPT() except +

        void initAnalysis(string, int)
        long getEventsNumber()
        int getEvent(long)
        #void printEvent()

        int getGeantTrackNum()
        int getGeantFibersRawNum()
        int getFibersStackCalSimNum()
        int getFibersStackCalNum()

        _MGeantTrack * getGeantTrack(int)
        _MGeantFibersRaw * getGeantFibersRaw(int)
        _MFibersStackCalSim * getFibersStackCalSim(int)
        _MFibersStackCal * getFibersStackCal(int)

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
    def getFibersStackCalSimNum(self):
        return self.c_obj.getFibersStackCalSimNum()
    def getFibersStackCalNum(self):
        return self.c_obj.getFibersStackCalNum()

    def getGeantTrack(self, i):
        _mgt = self.c_obj.getGeantTrack(i)
        cdef mgt = MGeantTrack.create(_mgt)
        return mgt

    def getGeantFibersRaw(self, i):
        _mgfr = self.c_obj.getGeantFibersRaw(i)
        cdef mgfr = MGeantFibersRaw.create(_mgfr)
        return mgfr

    def getFibersStackCalSim(self, i):
        _mfcs = self.c_obj.getFibersStackCalSim(i)
        cdef mfcs = MFibersStackCalSim.create(_mfcs)
        return mfcs

    def getFibersStackCal(self, i):
        _mfc = self.c_obj.getFibersStackCal(i)
        cdef mfc = MFibersStackCal.create(_mfc)
        return mfc
