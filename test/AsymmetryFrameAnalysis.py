#!/usr/bin/env python

import FWCore.ParameterSet.Config as cms

from SUSYBSMAnalysis.Zprime2muAnalysis.Zprime2muAnalysis_cfg import process
from SUSYBSMAnalysis.Zprime2muAnalysis.Zprime2muAnalysis_cff import Zprime2muAnalysisCommon
from SUSYBSMAnalysis.Zprime2muAnalysis.AsymFitManager_cff import AsymFitManager

process.AsymmetryFrameAnalysis = cms.EDAnalyzer('AsymmetryFrameAnalysis',
                                                Zprime2muAnalysisCommon,
                                                AsymFitManager,
                                                dilepton_src = cms.InputTag('dimuons'),
                                                debug = cms.untracked.bool(True),
                                                )

process.p = cms.Path(process.Zprime2muAnalysisSequence * process.AsymmetryFrameAnalysis)