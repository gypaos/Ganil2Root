include ./Makefile.arch

INCLUDE_PERSO  = -I$(NPTOOL)/NPLib/include
INCLUDE_GRU    = -I$(GRUDIR)/include -I$(GRUDIR)/MFMlib

SRCS = $(wildcard *.cxx)
OBJS = $(patsubst *.cxx,*.o,$(SRCS))

#------------------------------------------------------------------------------
SHARELIB      = libG2rDetector.so \
      		    libG2rModularLabel.so \
							libG2rMust2.so \
              libG2rCharissa.so \
              libG2rTiaraBarrel.so   libG2rTiaraHyball.so \
      		    libG2rCATS.so \
      		    libG2rSSSD.so \
      		    libG2rPlastic.so \
	libG2rLaBr3.so \
	libG2rSiLi.so \
	libG2rSiRes.so \
      		    libG2rChio_an.so \
      		    libG2rChio_dig.so \
		          libG2rS1.so \
		          libG2rVamosPlastic.so	libG2rVamosFinger.so \
		          libG2rVamosCHIO.so		libG2rVamosDC.so \
		          libG2rExogam.so \
      		    libG2rLiseData.so libG2rLise.so \
      		    libG2rTrigger.so \
              libG2rMaya.so \
              libG2rChateauCristal.so \
         		  libG2rExl.so \
		          libG2rSpegDC.so	libG2rSpegCHIO.so	libG2rSpegPlastic.so

all:            $(SHARELIB)
#------------------------------------------------------------------------------
libG2rModularLabel.so:   TModularLabel.o   TModularLabelDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TModularLabelDict.cxx:   TModularLabel.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^ 

libG2rMust2.so:   TMust2.o   TMust2Dict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TMust2Dict.cxx:   TMust2.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^ 

libG2rCharissa.so:   TCharissa.o   TCharissaDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TCharissaDict.cxx:   TCharissa.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^ 

libG2rTiaraBarrel.so:   TTiaraBarrel.o   TTiaraBarrelDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TTiaraBarrelDict.cxx:   TTiaraBarrel.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^ 

libG2rTiaraHyball.so:   TTiaraHyball.o   TTiaraHyballDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TTiaraHyballDict.cxx:   TTiaraHyball.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^ 

libG2rCATS.so: TCATS.o   TCATSDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TCATSDict.cxx: TCATS.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rSSSD.so: TSSSD.o   TSSSDDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TSSSDDict.cxx: TSSSD.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^ 

libG2rS1.so: TS1.o   TS1Dict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TS1Dict.cxx: TS1.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^ 

libG2rPlastic.so: TPlastic.o   TPlasticDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TLaBr3Dict.cxx: TLaBr3.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rLaBr3.so: TLaBr3.o   TLaBr3Dict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TSiLiDict.cxx: TSiLi.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rSiLi.so: TSiLi.o   TSiLiDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TSiResDict.cxx: TSiRes.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rSiRes.so: TSiRes.o   TSiResDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TPlasticDict.cxx: TPlastic.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rChio_an.so: TChio_an.o   TChio_anDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TChio_anDict.cxx: TChio_an.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rExogam.so:   TExogam.o   TExogamDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TExogamDict.cxx:        TExogam.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rVamosPlastic.so:     TVamosPlastic.o   TVamosPlasticDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TVamosPlasticDict.cxx:  TVamosPlastic.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rVamosFinger.so:      TVamosFinger.o   TVamosFingerDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TVamosFingerDict.cxx:   TVamosFinger.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rVamosCHIO.so:        TVamosCHIO.o   TVamosCHIODict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TVamosCHIODict.cxx:     TVamosCHIO.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rVamosDC.so:  TVamosDC.o   TVamosDCDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TVamosDCDict.cxx:       TVamosDC.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rLise.so: TLise.o   TLiseDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TLiseDict.cxx: TLise.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rLiseData.so:   TLiseData.o   TLiseDataDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TLiseDataDict.cxx:   TLiseData.h
	rootcint -f $@ -c $^

libG2rChio_dig.so:   TChio_dig.o   TChio_digDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TChio_digDict.cxx:   TChio_dig.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rTrigger.so: TTrigger.o   TTriggerDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TTriggerDict.cxx: TTrigger.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rMaya.so: TMaya.o   TMayaDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TMayaDict.cxx: TMaya.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rExl.so: TExl.o   TExlDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TExlDict.cxx: TExl.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rSpegDC.so: TSpegDC.o   TSpegDCDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TSpegDCDict.cxx: TSpegDC.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rSpegCHIO.so: TSpegCHIO.o   TSpegCHIODict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TSpegCHIODict.cxx: TSpegCHIO.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rSpegPlastic.so: TSpegPlastic.o   TSpegPlasticDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TSpegPlasticDict.cxx: TSpegPlastic.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rChateauCristal.so: TChateauCristal.o   TChateauCristalDict.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TChateauCristalDict.cxx: TChateauCristal.h
	rootcint -f $@ -c $(INCLUDE_PERSO) $(INCLUDE_GRU) $^

libG2rDetector.so:   TDetector.o   TDetectorDict.o TDetectorManager.o
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@

TDetectorDict.cxx:   TDetector.h
	rootcint -f $@ -c $(INCLUDE_GRU) $^

clean:
	@rm -f core *~ *.o *Dict*

distclean:
	make clean; rm -f *.so

.SUFFIXES: .$(SrcSuf)

###

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) $(INCLUDE_PERSO) $(INCLUDE_GRU) -c $<

# dependances
TDetectorManager.o: TDetectorManager.cxx TDetectorManager.h TDetector.o
TDetector.o:   TDetector.cxx  TDetector.h
TMust2.o:   TMust2.cxx  TMust2.h
TCharissa.o:   TCharissa.cxx  TCharissa.h
TTiaraBarrel.o:   TTiaraBarrel.cxx  TTiaraBarrel.h
TTiaraHyball.o:   TTiaraHyball.cxx  TTiaraHyball.h
TCATS.o: TCATS.cxx   TCATS.h
TSSSD.o: TSSSD.cxx   TSSSD.h
TPlastic.o: TPlastic.cxx   TPlastic.h
TLaBr3.o: TLaBr3.cxx   TLaBr3.h
TSiLi.o: TSiLi.cxx   TSiLi.h
TSiRes.o: TSiRes.cxx   TSiRes.h
TVamosPlastic.o:        TVamosPlastic.cxx       TVamosPlastic.h
TVamosFinger.o:         TVamosFinger.cxx        TVamosFinger.h
TVamosCHIO.o:           TVamosCHIO.cxx          TVamosCHIO.h
TVamosDC.o:     TVamosDC.cxx            TVamosDC.h
TChio_an.o: TChio_an.cxx   TChio_an.h
TChio_dig.o:   TChio_dig.cxx  TChio_dig.h
TTrigger.o: TTrigger.cxx      TTrigger.h
TLiseData.o:   TLiseData.cxx  TLiseData.h
TLise.o:       TLise.cxx      TLise.h
TChateauCristal.o:       TChateauCristal.cxx      TChateauCristal.h
TMaya.o:       TMaya.cxx      TMaya.h
TExl.o:		TExl.cxx	TExl.h
TSpegDC.o:	TSpegDC.cxx	TSpegDC.h
TSpegCHIO.o:	TSpegCHIO.cxx	TSpegCHIO.h
TSpegPlastic.o:	TSpegPlastic.cxx	TSpegPlastic.h
