/* ---------------------------------------------------------------------------------
** Event Alignment Histograms for Alignment between WaveForms and Telescope Planes
**
**
** <EventAlignmentHistos>.hh
**
** Date: May 2016
** Author: Michael Reichmann (remichae@phys.ethz.ch)
** ---------------------------------------------------------------------------------*/

#ifndef EUDAQ_EVENTALIGNMENTHISTOS_HH
#define EUDAQ_EVENTALIGNMENTHISTOS_HH

class TH1;
class TH2I;
class TProfile;
class SimpleStandardEvent;
class RootMonitor;
class TString;

#include <cstdint>
#include <string>

class EventAlignmentHistos{

protected:
    TH1 * _Alignment;
    TH1 * _AlignmentPlus1;
    TH2I * _IsAligned;
    TH2I * _IsAlignedPlus1;
    uint16_t _lastNClusters;

public:
    EventAlignmentHistos();
    virtual ~EventAlignmentHistos();
    void Fill(const SimpleStandardEvent&);
    void Write();
    void Reset();
    TProfile * getAlignmentHisto() { return (TProfile*)_Alignment; }
    TProfile *  getAlignmentPlus1Histo() { return (TProfile*)_AlignmentPlus1; }
    TH2I * getIsAlignedHisto() { return _IsAligned; }
    TH2I * getIsAlignedPlus1Histo() { return _IsAlignedPlus1; }

private:
    uint16_t bin_size;
    uint32_t max_event_number;
    TProfile * init_profile(std::string, std::string);
    TH2I * init_th2i(std::string, std::string);
    void FillIsAligned(TProfile*, TH2I*);
};


#ifdef __CINT__
#pragma link C++ class EventAlignmentHistos-;
#endif

#endif //EUDAQ_EVENTALIGNMENTHISTOS_HH