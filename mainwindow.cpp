#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QtGlobal>
#include <QFileDialog>
#include <QSettings>
#include <QProgressDialog>
#include <QHBoxLayout>

#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TPad.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLine.h>
#include <TMultiGraph.h>

#include <iomanip>
#include <fstream>
#include <bitset>
#include <cstring>
#include <algorithm>
#include <numeric>

// RapidJSON includes
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/filereadstream.h"

namespace {
/*
constexpr std::array< int, CHANNELS_PER_CHIP > ChamberStrips{
  9,
  10,
  11,
  12,
  25,
  26,
  27,
  28,
  13,
  14,
  15,
  16,
  29,
  30,
  31,
  32,
  17,
  18,
  19,
  20,
  1,
  2,
  3,
  4,
  21,
  22,
  23,
  24,
  5,
  6,
  7,
  8
};
*/
constexpr std::array< std::pair< int, int >, CHANNELS_PER_CHIP * 4 > VerticalChipChannelStrips{
  std::pair< int, int >( 11, 8 ),
  std::pair< int, int >( 11, 7 ),
  std::pair< int, int >( 11, 6 ),
  std::pair< int, int >( 11, 5 ),
  std::pair< int, int >( 11, 24 ),
  std::pair< int, int >( 11, 23 ),
  std::pair< int, int >( 11, 22 ),
  std::pair< int, int >( 11, 21 ),
  std::pair< int, int >( 11, 4 ),
  std::pair< int, int >( 11, 3 ),
  std::pair< int, int >( 11, 2 ),
  std::pair< int, int >( 11, 1 ),
  std::pair< int, int >( 11, 20 ),
  std::pair< int, int >( 11, 19 ),
  std::pair< int, int >( 11, 18 ),
  std::pair< int, int >( 11, 17 ),
  std::pair< int, int >( 11, 32 ),
  std::pair< int, int >( 11, 31 ),
  std::pair< int, int >( 11, 30 ),
  std::pair< int, int >( 11, 29 ),
  std::pair< int, int >( 11, 16 ),
  std::pair< int, int >( 11, 15 ),
  std::pair< int, int >( 11, 14 ),
  std::pair< int, int >( 11, 13 ),
  std::pair< int, int >( 11, 28 ),
  std::pair< int, int >( 11, 27 ),
  std::pair< int, int >( 11, 26 ),
  std::pair< int, int >( 11, 25 ),
  std::pair< int, int >( 11, 12 ),
  std::pair< int, int >( 11, 11 ),
  std::pair< int, int >( 11, 10 ),
  std::pair< int, int >( 11, 9 ),
  std::pair< int, int >( 2, 8 ),
  std::pair< int, int >( 2, 7 ),
  std::pair< int, int >( 2, 6 ),
  std::pair< int, int >( 2, 5 ),
  std::pair< int, int >( 2, 24 ),
  std::pair< int, int >( 2, 23 ),
  std::pair< int, int >( 2, 22 ),
  std::pair< int, int >( 2, 21 ),
  std::pair< int, int >( 2, 4 ),
  std::pair< int, int >( 2, 3 ),
  std::pair< int, int >( 2, 2 ),
  std::pair< int, int >( 2, 1 ),
  std::pair< int, int >( 2, 20 ),
  std::pair< int, int >( 2, 19 ),
  std::pair< int, int >( 2, 18 ),
  std::pair< int, int >( 2, 17 ),
  std::pair< int, int >( 2, 32 ),
  std::pair< int, int >( 2, 31 ),
  std::pair< int, int >( 2, 30 ),
  std::pair< int, int >( 2, 29 ),
  std::pair< int, int >( 2, 16 ),
  std::pair< int, int >( 2, 15 ),
  std::pair< int, int >( 2, 14 ),
  std::pair< int, int >( 2, 13 ),
  std::pair< int, int >( 2, 28 ),
  std::pair< int, int >( 2, 27 ),
  std::pair< int, int >( 2, 26 ),
  std::pair< int, int >( 2, 25 ),
  std::pair< int, int >( 2, 12 ),
  std::pair< int, int >( 2, 11 ),
  std::pair< int, int >( 2, 10 ),
  std::pair< int, int >( 2, 9 ),
  std::pair< int, int >( 12, 8 ),
  std::pair< int, int >( 12, 7 ),
  std::pair< int, int >( 12, 6 ),
  std::pair< int, int >( 12, 5 ),
  std::pair< int, int >( 12, 24 ),
  std::pair< int, int >( 12, 23 ),
  std::pair< int, int >( 12, 22 ),
  std::pair< int, int >( 12, 21 ),
  std::pair< int, int >( 12, 4 ),
  std::pair< int, int >( 12, 3 ),
  std::pair< int, int >( 12, 2 ),
  std::pair< int, int >( 12, 1 ),
  std::pair< int, int >( 12, 20 ),
  std::pair< int, int >( 12, 19 ),
  std::pair< int, int >( 12, 18 ),
  std::pair< int, int >( 12, 17 ),
  std::pair< int, int >( 12, 32 ),
  std::pair< int, int >( 12, 31 ),
  std::pair< int, int >( 12, 30 ),
  std::pair< int, int >( 12, 29 ),
  std::pair< int, int >( 12, 16 ),
  std::pair< int, int >( 12, 15 ),
  std::pair< int, int >( 12, 14 ),
  std::pair< int, int >( 12, 13 ),
  std::pair< int, int >( 12, 28 ),
  std::pair< int, int >( 12, 27 ),
  std::pair< int, int >( 12, 26 ),
  std::pair< int, int >( 12, 25 ),
  std::pair< int, int >( 12, 12 ),
  std::pair< int, int >( 12, 11 ),
  std::pair< int, int >( 12, 10 ),
  std::pair< int, int >( 12, 9 ),
  std::pair< int, int >( 1, 9 ),
  std::pair< int, int >( 1, 10 ),
  std::pair< int, int >( 1, 11 ),
  std::pair< int, int >( 1, 12 ),
  std::pair< int, int >( 1, 25 ),
  std::pair< int, int >( 1, 26 ),
  std::pair< int, int >( 1, 27 ),
  std::pair< int, int >( 1, 28 ),
  std::pair< int, int >( 1, 13 ),
  std::pair< int, int >( 1, 14 ),
  std::pair< int, int >( 1, 15 ),
  std::pair< int, int >( 1, 16 ),
  std::pair< int, int >( 1, 29 ),
  std::pair< int, int >( 1, 30 ),
  std::pair< int, int >( 1, 31 ),
  std::pair< int, int >( 1, 32 ),
  std::pair< int, int >( 1, 17 ),
  std::pair< int, int >( 1, 18 ),
  std::pair< int, int >( 1, 19 ),
  std::pair< int, int >( 1, 20 ),
  std::pair< int, int >( 1, 1 ),
  std::pair< int, int >( 1, 2 ),
  std::pair< int, int >( 1, 3 ),
  std::pair< int, int >( 1, 4 ),
  std::pair< int, int >( 1, 21 ),
  std::pair< int, int >( 1, 22 ),
  std::pair< int, int >( 1, 23 ),
  std::pair< int, int >( 1, 24 ),
  std::pair< int, int >( 1, 5 ),
  std::pair< int, int >( 1, 6 ),
  std::pair< int, int >( 1, 7 ),
  std::pair< int, int >( 1, 8 )
};

/*
constexpr std::array< std::pair< int, int >, CHANNELS_PER_PLANE > HorizontalChipChannelStrips{
  std::pair< int, int >( 4, 9 ),
  std::pair< int, int >( 4, 10 ),
  std::pair< int, int >( 4, 11 ),
  std::pair< int, int >( 4, 12 ),
  std::pair< int, int >( 4, 25 ),
  std::pair< int, int >( 4, 26 ),
  std::pair< int, int >( 4, 27 ),
  std::pair< int, int >( 4, 28 ),
  std::pair< int, int >( 4, 13 ),
  std::pair< int, int >( 4, 14 ),
  std::pair< int, int >( 4, 15 ),
  std::pair< int, int >( 4, 16 ),
  std::pair< int, int >( 4, 29 ),
  std::pair< int, int >( 4, 30 ),
  std::pair< int, int >( 4, 31 ),
  std::pair< int, int >( 4, 32 ),
  std::pair< int, int >( 4, 17 ),
  std::pair< int, int >( 4, 18 ),
  std::pair< int, int >( 4, 19 ),
  std::pair< int, int >( 4, 20 ),
  std::pair< int, int >( 4, 1 ),
  std::pair< int, int >( 4, 2 ),
  std::pair< int, int >( 4, 3 ),
  std::pair< int, int >( 4, 4 ),
  std::pair< int, int >( 4, 21 ),
  std::pair< int, int >( 4, 22 ),
  std::pair< int, int >( 4, 23 ),
  std::pair< int, int >( 4, 24 ),
  std::pair< int, int >( 4, 5 ),
  std::pair< int, int >( 4, 6 ),
  std::pair< int, int >( 4, 7 ),
  std::pair< int, int >( 4, 8 ),
  std::pair< int, int >( 11, 9 ),
  std::pair< int, int >( 11, 10 ),
  std::pair< int, int >( 11, 11 ),
  std::pair< int, int >( 11, 12 ),
  std::pair< int, int >( 11, 25 ),
  std::pair< int, int >( 11, 26 ),
  std::pair< int, int >( 11, 27 ),
  std::pair< int, int >( 11, 28 ),
  std::pair< int, int >( 11, 13 ),
  std::pair< int, int >( 11, 14 ),
  std::pair< int, int >( 11, 15 ),
  std::pair< int, int >( 11, 16 ),
  std::pair< int, int >( 11, 29 ),
  std::pair< int, int >( 11, 30 ),
  std::pair< int, int >( 11, 31 ),
  std::pair< int, int >( 11, 32 ),
  std::pair< int, int >( 11, 17 ),
  std::pair< int, int >( 11, 18 ),
  std::pair< int, int >( 11, 19 ),
  std::pair< int, int >( 11, 20 ),
  std::pair< int, int >( 11, 1 ),
  std::pair< int, int >( 11, 2 ),
  std::pair< int, int >( 11, 3 ),
  std::pair< int, int >( 11, 4 ),
  std::pair< int, int >( 11, 21 ),
  std::pair< int, int >( 11, 22 ),
  std::pair< int, int >( 11, 23 ),
  std::pair< int, int >( 11, 24 ),
  std::pair< int, int >( 11, 5 ),
  std::pair< int, int >( 11, 6 ),
  std::pair< int, int >( 11, 7 ),
  std::pair< int, int >( 11, 8 ),
  std::pair< int, int >( 12, 9 ),
  std::pair< int, int >( 12, 10 ),
  std::pair< int, int >( 12, 11 ),
  std::pair< int, int >( 12, 12 ),
  std::pair< int, int >( 12, 25 ),
  std::pair< int, int >( 12, 26 ),
  std::pair< int, int >( 12, 27 ),
  std::pair< int, int >( 12, 28 ),
  std::pair< int, int >( 12, 13 ),
  std::pair< int, int >( 12, 14 ),
  std::pair< int, int >( 12, 15 ),
  std::pair< int, int >( 12, 16 ),
  std::pair< int, int >( 12, 29 ),
  std::pair< int, int >( 12, 30 ),
  std::pair< int, int >( 12, 31 ),
  std::pair< int, int >( 12, 32 ),
  std::pair< int, int >( 12, 17 ),
  std::pair< int, int >( 12, 18 ),
  std::pair< int, int >( 12, 19 ),
  std::pair< int, int >( 12, 20 ),
  std::pair< int, int >( 12, 1 ),
  std::pair< int, int >( 12, 2 ),
  std::pair< int, int >( 12, 3 ),
  std::pair< int, int >( 12, 4 ),
  std::pair< int, int >( 12, 21 ),
  std::pair< int, int >( 12, 22 ),
  std::pair< int, int >( 12, 23 ),
  std::pair< int, int >( 12, 24 ),
  std::pair< int, int >( 12, 5 ),
  std::pair< int, int >( 12, 6 ),
  std::pair< int, int >( 12, 7 ),
  std::pair< int, int >( 12, 8 ),
  std::pair< int, int >( 10, 8 ),
  std::pair< int, int >( 10, 7 ),
  std::pair< int, int >( 10, 6 ),
  std::pair< int, int >( 10, 5 ),
  std::pair< int, int >( 10, 24 ),
  std::pair< int, int >( 10, 23 ),
  std::pair< int, int >( 10, 22 ),
  std::pair< int, int >( 10, 21 ),
  std::pair< int, int >( 10, 4 ),
  std::pair< int, int >( 10, 3 ),
  std::pair< int, int >( 10, 2 ),
  std::pair< int, int >( 10, 1 ),
  std::pair< int, int >( 10, 20 ),
  std::pair< int, int >( 10, 19 ),
  std::pair< int, int >( 10, 18 ),
  std::pair< int, int >( 10, 17 ),
  std::pair< int, int >( 10, 32 ),
  std::pair< int, int >( 10, 31 ),
  std::pair< int, int >( 10, 30 ),
  std::pair< int, int >( 10, 29 ),
  std::pair< int, int >( 10, 16 ),
  std::pair< int, int >( 10, 15 ),
  std::pair< int, int >( 10, 14 ),
  std::pair< int, int >( 10, 13 ),
  std::pair< int, int >( 10, 28 ),
  std::pair< int, int >( 10, 27 ),
  std::pair< int, int >( 10, 26 ),
  std::pair< int, int >( 10, 25 ),
  std::pair< int, int >( 10, 12 ),
  std::pair< int, int >( 10, 11 ),
  std::pair< int, int >( 10, 10 ),
  std::pair< int, int >( 10, 9 ),
  std::pair< int, int >( 2, 8 ),
  std::pair< int, int >( 2, 7 ),
  std::pair< int, int >( 2, 6 ),
  std::pair< int, int >( 2, 5 ),
  std::pair< int, int >( 2, 24 ),
  std::pair< int, int >( 2, 23 ),
  std::pair< int, int >( 2, 22 ),
  std::pair< int, int >( 2, 21 ),
  std::pair< int, int >( 2, 4 ),
  std::pair< int, int >( 2, 3 ),
  std::pair< int, int >( 2, 2 ),
  std::pair< int, int >( 2, 1 ),
  std::pair< int, int >( 2, 20 ),
  std::pair< int, int >( 2, 19 ),
  std::pair< int, int >( 2, 18 ),
  std::pair< int, int >( 2, 17 ),
  std::pair< int, int >( 2, 32 ),
  std::pair< int, int >( 2, 31 ),
  std::pair< int, int >( 2, 30 ),
  std::pair< int, int >( 2, 29 ),
  std::pair< int, int >( 2, 16 ),
  std::pair< int, int >( 2, 15 ),
  std::pair< int, int >( 2, 14 ),
  std::pair< int, int >( 2, 13 ),
  std::pair< int, int >( 2, 28 ),
  std::pair< int, int >( 2, 27 ),
  std::pair< int, int >( 2, 26 ),
  std::pair< int, int >( 2, 25 ),
  std::pair< int, int >( 2, 12 ),
  std::pair< int, int >( 2, 11 ),
  std::pair< int, int >( 2, 10 ),
  std::pair< int, int >( 2, 9 ),
  std::pair< int, int >( 9, 8 ),
  std::pair< int, int >( 9, 7 ),
  std::pair< int, int >( 9, 6 ),
  std::pair< int, int >( 9, 5 ),
  std::pair< int, int >( 9, 24 ),
  std::pair< int, int >( 9, 23 ),
  std::pair< int, int >( 9, 22 ),
  std::pair< int, int >( 9, 21 ),
  std::pair< int, int >( 9, 4 ),
  std::pair< int, int >( 9, 3 ),
  std::pair< int, int >( 9, 2 ),
  std::pair< int, int >( 9, 1 ),
  std::pair< int, int >( 9, 20 ),
  std::pair< int, int >( 9, 19 ),
  std::pair< int, int >( 9, 18 ),
  std::pair< int, int >( 9, 17 ),
  std::pair< int, int >( 9, 32 ),
  std::pair< int, int >( 9, 31 ),
  std::pair< int, int >( 9, 30 ),
  std::pair< int, int >( 9, 29 ),
  std::pair< int, int >( 9, 16 ),
  std::pair< int, int >( 9, 15 ),
  std::pair< int, int >( 9, 14 ),
  std::pair< int, int >( 9, 13 ),
  std::pair< int, int >( 9, 28 ),
  std::pair< int, int >( 9, 27 ),
  std::pair< int, int >( 9, 26 ),
  std::pair< int, int >( 9, 25 ),
  std::pair< int, int >( 9, 12 ),
  std::pair< int, int >( 9, 11 ),
  std::pair< int, int >( 9, 10 ),
  std::pair< int, int >( 9, 9 )
};
*/
const std::map< int, std::array< int, 4 > > VerticalStripsCalibration{
  std::pair< int, std::array< int, 4 > >( 0, { 75, 95, 171, 191 }),
  std::pair< int, std::array< int, 4 > >( 2, { 65, 80, 161, 178 }),
  std::pair< int, std::array< int, 4 > >( 3, { 53, 70, 151, 167 }),
  std::pair< int, std::array< int, 4 > >( 5, { 43, 60, 140, 156 }),
  std::pair< int, std::array< int, 4 > >( 6, { 33, 46, 130, 146 }),
  std::pair< int, std::array< int, 4 > >( 7, { 23, 38, 117, 135 }),
  std::pair< int, std::array< int, 4 > >( 8, { 10, 28, 107, 124 }),
  std::pair< int, std::array< int, 4 > >( 9, { 0, 15, 96, 113 })
};

const std::map< int, std::array< int, 4 > > HorizontalStripsCalibration{
  std::pair< int, std::array< int, 4 > >( 0, { 73, 95, 170, 191 }),
  std::pair< int, std::array< int, 4 > >( 1, { 64, 79, 161, 176 }),
  std::pair< int, std::array< int, 4 > >( 2, { 52, 68, 149, 165 }),
  std::pair< int, std::array< int, 4 > >( 3, { 42, 60, 139, 156 }),
  std::pair< int, std::array< int, 4 > >( 4, { 31, 47, 130, 145 }),
  std::pair< int, std::array< int, 4 > >( 5, { 20, 37, 116, 134 }),
  std::pair< int, std::array< int, 4 > >( 6, { 10, 28, 105, 123 }),
  std::pair< int, std::array< int, 4 > >( 7, { 0, 15, 96, 113 })
};

constexpr int RESOLUTION_16BIT = (1 << AdcResolutionType::ADC_16_BIT);
constexpr int RESOLUTION_18BIT = (1 << AdcResolutionType::ADC_18_BIT);
constexpr int RESOLUTION_20BIT = (1 << AdcResolutionType::ADC_20_BIT);

constexpr int ADC_WORDS_PER_CHANNEL = 2;
constexpr int ADC_CHANNELS_PER_CHUNK = ADC_WORDS_PER_CHANNEL * CHANNELS_PER_CHIP;
constexpr int BITS = CHAR_BIT * 2;

/// Camera1
/// std::array< int, CHIPS_PER_PLANE > ChipsVerticalStrips{ 7, 3, 5, 6, 1, 8  };
/// std::array< int, CHIPS_PER_PLANE > ChipsHorizontalStrips{ 10, 11, 12, 4, 2, 9 };

/// Camera2
std::array< int, 4 > ChipsVerticalStrips{ 11, 2, 12, 1 };
std::array< int, CHIPS_PER_PLANE > ChipsHorizontalStrips{ 6, 3, 5, 9, 4, 10 };

constexpr std::array< Double_t, ChipsHorizontalStrips.size() * CHANNELS_PER_CHIP > GraphHorizontalStrips{};
constexpr std::array< Double_t, ChipsVerticalStrips.size() * CHANNELS_PER_CHIP > GraphVerticalStrips{};

constexpr std::array< double, CHAR_BIT > CapacityChargeCoefficient{ 12.5, 50., 100., 150., 200., 250., 300., 350. };
constexpr std::array< double, CHAR_BIT > CapacityCoefficient{ 3.0, 12.5, 25., 37.5, 50., 62.5, 75., 87.5 };

constexpr size_t BUFFER_SIZE = 3;

template< size_t N >
std::array< Double_t, N > GenerateStripsNumbers(int init = 1) {
  std::array< Double_t, N > v;
  std::iota(std::begin(v), std::end(v), init);
  return v;
}

template< size_t N >
std::array< Double_t, N > GenerateVerticalStripsBinsBordersRaw()
{
  std::array< Double_t, N > v;
  v[0] = 0.;
  for (size_t i = 1; i < v.size(); ++i)
  {
    v[i] = v[i - 1] + 2.;
  }
  return v;
}

template< size_t N >
std::array< Double_t, N > GenerateVerticalStripsBinsBordersCorrect()
{
  std::array< Double_t, N > v;
  v[0] = 0.0;
  for (size_t i = 1; i < CHANNELS_PER_CHIP; ++i)
  {
    v[i] = v[i - 1] + 2.; // 2 mm step
  }
  for (size_t i = CHANNELS_PER_CHIP; i < 3 * CHANNELS_PER_CHIP; ++i)
  {
    v[i] = v[i - 1] + 1.; // 1 mm step
  }
  for (size_t i = 3 * CHANNELS_PER_CHIP; i < v.size(); ++i)
  {
    v[i] = v[i - 1] + 2.; // 2 mm step
  }
  return v;
}

template< size_t N >
std::array< Double_t, N > GenerateHorizontalStripsBinsBordersCorrect()
{
  std::array< Double_t, N > v;
  v[0] = 0.0;
  for (size_t i = 1; i < v.size(); ++i)
  {
    v[i] = v[i - 1] + 1.;
  }
  return v;
}

const std::array< Double_t, GraphHorizontalStrips.size() > GraphHorizontalStripsNumbers = GenerateStripsNumbers< GraphHorizontalStrips.size() >();
const std::array< Double_t, GraphVerticalStrips.size() > GraphVerticalStripsNumbers = GenerateStripsNumbers< GraphVerticalStrips.size() >();

const std::array< Double_t, CHANNELS_PER_CHIP * 4 + 1 > VerticalStripsBinsCorrect = GenerateVerticalStripsBinsBordersCorrect< CHANNELS_PER_CHIP * 4 + 1 >();
const std::array< Double_t, CHANNELS_PER_CHIP * 4 + 1 > VerticalStripsBinsRaw = GenerateVerticalStripsBinsBordersRaw< CHANNELS_PER_CHIP * 4 + 1 >();

const std::array< Double_t, CHANNELS_PER_PLANE > HorizontalStripsBinsCorrect = GenerateHorizontalStripsBinsBordersCorrect< CHANNELS_PER_PLANE >();
const std::array< Double_t, CHANNELS_PER_PLANE > HorizontalStripsBinsRaw = GenerateVerticalStripsBinsBordersRaw< CHANNELS_PER_PLANE >();

const QByteArray FirstContactCommand( 1, 'A');
const QByteArray SingleShotCommand( "S\0\0", BUFFER_SIZE);
const QByteArray AcquisitionCommand( "B\0\0", BUFFER_SIZE);
const QByteArray ChipResetCommand( "H\0\0", BUFFER_SIZE);
const QByteArray AlteraResetCommand( "R\0\0", BUFFER_SIZE);
const QByteArray WriteCapacitiesCommand( "G\0\0", BUFFER_SIZE); // write DDC232 configuration register
const QByteArray ListChipsEnabledCommand( "L\0\0", BUFFER_SIZE); // list of chips enabled

template< size_t N >
void ReverseBits(std::bitset< N >& b)
{
  for (size_t i = 0; i < N / 2; ++i)
  {
    bool t = b[i];
    b[i] = b[N - i - 1];
    b[N - i - 1] = t;
  }
}

std::map< std::pair< int, int >, std::vector< double > > AmplitudeCalibrationMap;

}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , timer(new QTimer(this))
  , initiationProgress(new QProgressDialog(this))
  , spillTimeoutTimer(new QTimer(this))
  , initiationTimer(new QTimer(this))
{
  ui->setupUi(this);

  for (int i = 0; i < CHIPS_PER_PLANE * 2; ++i)
  {
    this->CheckBox_DevicesEnabled[i] = new QCheckBox( tr("%1").arg(i + 1), this);
    this->ui->HorizontalLayout_DevicesEnabled->insertWidget( i, CheckBox_DevicesEnabled[i]);
    this->CheckBox_DevicesEnabled[i]->setChecked(true);
  }

  for (int i = 1; i <= CHIPS_PER_PLANE * 2; ++i)
  {
    for (int j = 1; j <= CHANNELS_PER_CHIP; ++j)
    {
      std::pair< int, int > chipChannelPair(i, j);
      AmplitudeCalibrationMap.insert({chipChannelPair, std::vector< double >() });
      this->chipChannelCalibrationA.insert({chipChannelPair, 1.0 });
      this->chipChannelCalibrationB.insert({chipChannelPair, 1.0 });
      this->chipChannelCalibrationAmplitude.insert({chipChannelPair, 1.0 });
    }
  }
  this->initiationProgress->setWindowTitle(tr("Ionization chamber"));
  this->initiationProgress->setLabelText("Chips initiation...");

  this->rootCanvas[StripsOrientationType::ORIENTATION_HORIZONTAL] = this->ui->RootCanvas_HorizontalStrips->getCanvas();
  this->rootCanvas[StripsOrientationType::ORIENTATION_VERTICAL] = this->ui->RootCanvas_VerticalStrips->getCanvas();
  this->getHorizontalStripsCanvas()->Divide(2, 1);
  this->getVerticalStripsCanvas()->Divide(2, 1);

  this->hist2Strips[StripsOrientationType::ORIENTATION_HORIZONTAL] = new TH2F( "hist2Hor", "Horizontal Strips",
    ChipsHorizontalStrips.size() * CHANNELS_PER_CHIP, -.5,
    double(ChipsHorizontalStrips.size() * CHANNELS_PER_CHIP) - .5,
    RESOLUTION_18BIT / 16, -1000., double(RESOLUTION_18BIT) / 4 - 1001.);
//    512, -0.01, 1. - 0.01);
  this->hist2Strips[StripsOrientationType::ORIENTATION_VERTICAL] = new TH2F( "hist2Ver", "Vertical Strips",
    ChipsVerticalStrips.size() * CHANNELS_PER_CHIP, -.5,
    double(ChipsVerticalStrips.size() * CHANNELS_PER_CHIP) - .5,
    RESOLUTION_18BIT / 16, -1000., double(RESOLUTION_18BIT) / 4 - 1001.);
//    512, -0.01, 1. - 0.01);
  this->graphFit[StripsOrientationType::ORIENTATION_VERTICAL] = new TGraphErrors(GraphVerticalStrips.size());
  this->graphFit[StripsOrientationType::ORIENTATION_HORIZONTAL] = new TGraphErrors(GraphHorizontalStrips.size());

  if (ui->RadioButton_Adc16Bit->isChecked())
  {
//    this->hist2Strips[StripsOrientationType::ORIENTATION_HORIZONTAL] = new TH2F( "hist2Hor", "Horizontal Strips",
//      CHANNELS_PER_PLANE, .5, double(CHANNELS_PER_PLANE) - .5, Resolution16Bit / 4, -1000., double(Resolution16Bit) - 1001.);
//    this->hist2Strips[StripsOrientationType::ORIENTATION_VERTICAL] = new TH2F( "hist2Ver", "Vertical Strips",
//      CHANNELS_PER_PLANE, .5, double(CHANNELS_PER_PLANE) - .5, Resolution16Bit / 4, -1000., double(Resolution16Bit) - 1001.);
    this->histChannel[ChannelSideType::SIDE_A] = new TH1F("histA", "Side-A", RESOLUTION_16BIT / 4, -1000., double(RESOLUTION_16BIT) - 1001.);
    this->histChannel[ChannelSideType::SIDE_B] = new TH1F("histB", "Side-B", RESOLUTION_16BIT / 4, -1000., double(RESOLUTION_16BIT) - 1001.);
  }
  else if (ui->RadioButton_Adc20Bit->isChecked())
  {
//    this->hist2Strips[StripsOrientationType::ORIENTATION_HORIZONTAL] = new TH2F( "hist2Hor", "Horizontal Strips",
//      CHANNELS_PER_PLANE, .5, double(CHANNELS_PER_PLANE) - .5, Resolution20Bit / 4, -1000., double(Resolution20Bit) - 1001.);
//    this->hist2Strips[StripsOrientationType::ORIENTATION_VERTICAL] = new TH2F( "hist2Ver", "Vertical Strips",
//      CHANNELS_PER_PLANE, .5, double(CHANNELS_PER_PLANE) - .5, Resolution20Bit / 4, -1000., double(Resolution20Bit) - 1001.);
    this->histChannel[ChannelSideType::SIDE_A] = new TH1F("histA", "Side-A", RESOLUTION_20BIT / 4, -1000., double(RESOLUTION_20BIT) - 1001.);
    this->histChannel[ChannelSideType::SIDE_B] = new TH1F("histB", "Side-B", RESOLUTION_20BIT / 4, -1000., double(RESOLUTION_20BIT) - 1001.);
  }

  this->getHorizontalStripsCanvas()->cd(1);
  this->hist2Pad[StripsOrientationType::ORIENTATION_HORIZONTAL] = dynamic_cast<TPad*>(this->getHorizontalStripsCanvas()->GetPad(1));
  this->hist2Pad[StripsOrientationType::ORIENTATION_HORIZONTAL]->Draw();
  this->hist2Pad[StripsOrientationType::ORIENTATION_HORIZONTAL]->SetGrid();
  this->hist2Pad[StripsOrientationType::ORIENTATION_HORIZONTAL]->cd();
  this->getHorizontalStripsHist()->Draw("COLZ");
  this->getHorizontalStripsHist()->GetXaxis()->SetTitle("Strips");
//  this->getHorizontalStripsHist()->GetYaxis()->SetTitle("Integrals per spill");
//  this->getHorizontalStripsHist()->GetYaxis()->SetTitle("Mean charge (pC)");
  this->getHorizontalStripsHist()->GetYaxis()->SetTitle("Mean signal ADC counts");

  this->getVerticalStripsCanvas()->cd(1);
  this->hist2Pad[StripsOrientationType::ORIENTATION_VERTICAL] = dynamic_cast<TPad*>(this->getVerticalStripsCanvas()->GetPad(1));
  this->hist2Pad[StripsOrientationType::ORIENTATION_VERTICAL]->Draw();
  this->hist2Pad[StripsOrientationType::ORIENTATION_VERTICAL]->SetGrid();
  this->hist2Pad[StripsOrientationType::ORIENTATION_VERTICAL]->cd();
  this->getVerticalStripsHist()->Draw("COLZ");
  this->getVerticalStripsHist()->GetXaxis()->SetTitle("Strips");
//  this->getVerticalStripsHist()->GetYaxis()->SetTitle("Integrals per spill");
//  this->getVerticalStripsHist()->GetYaxis()->SetTitle("Mean charge (pC)");
  this->getVerticalStripsHist()->GetYaxis()->SetTitle("Mean signal ADC counts");

  constexpr Color_t colors[2] = { kBlack, kRed };
  this->multiGraphStrips[StripsOrientationType::ORIENTATION_HORIZONTAL] = new TMultiGraph( "mgHoriz", "Horizontal Strips (Vertical profile);Strips;Mean signal, ADC counts");
  this->multiGraphStrips[StripsOrientationType::ORIENTATION_VERTICAL] = new TMultiGraph( "mgVert", "Vertical Strips (Horizontal profile);Strips;Mean signal, ADC counts");
  this->graphStrips[StripsOrientationType::ORIENTATION_HORIZONTAL] = new TGraphErrors(ChipsHorizontalStrips.size() * CHANNELS_PER_CHIP, GraphHorizontalStripsNumbers.data(), GraphHorizontalStrips.data());
  this->graphStrips[StripsOrientationType::ORIENTATION_VERTICAL] = new TGraphErrors(ChipsVerticalStrips.size() * CHANNELS_PER_CHIP, GraphVerticalStripsNumbers.data(), GraphVerticalStrips.data());
  this->graphStripsCalibrated[StripsOrientationType::ORIENTATION_HORIZONTAL] = new TGraphErrors(ChipsHorizontalStrips.size() * CHANNELS_PER_CHIP, GraphHorizontalStripsNumbers.data(), GraphHorizontalStrips.data());
  this->graphStripsCalibrated[StripsOrientationType::ORIENTATION_VERTICAL] = new TGraphErrors(ChipsVerticalStrips.size() * CHANNELS_PER_CHIP, GraphVerticalStripsNumbers.data(), GraphVerticalStrips.data());
  this->getHorizontalStripsGraph()->SetLineColor(colors[0]);
  this->getHorizontalStripsGraph()->SetLineWidth(2);
  this->getHorizontalStripsGraph()->SetMarkerColor(colors[0]);
  this->getHorizontalCalibratedStripsGraph()->SetLineColor(colors[1]);
  this->getHorizontalCalibratedStripsGraph()->SetLineWidth(2);
  this->getHorizontalCalibratedStripsGraph()->SetMarkerColor(colors[1]);
  this->getVerticalStripsGraph()->SetLineColor(colors[0]);
  this->getVerticalStripsGraph()->SetLineWidth(2);
  this->getVerticalStripsGraph()->SetMarkerColor(colors[0]);
  this->getVerticalCalibratedStripsGraph()->SetLineColor(colors[1]);
  this->getVerticalCalibratedStripsGraph()->SetLineWidth(2);
  this->getVerticalCalibratedStripsGraph()->SetMarkerColor(colors[1]);
//  this->getHorizontalStripsGraph()->SetTitle("Horizontal Strips (Vertical profile);Strips;Spill integral");
//  this->getVerticalStripsGraph()->SetTitle("Vertical Strips (Horizontal profile);Strips;Spill integral");

  this->getHorizontalStripsMultiGraph()->Add( this->getHorizontalStripsGraph());
  this->getHorizontalStripsMultiGraph()->Add( this->getHorizontalCalibratedStripsGraph());
  this->getHorizontalStripsCanvas()->cd(2);
  this->graphPad[StripsOrientationType::ORIENTATION_HORIZONTAL] = dynamic_cast<TPad*>(this->getHorizontalStripsCanvas()->GetPad(2));
  this->graphPad[StripsOrientationType::ORIENTATION_HORIZONTAL]->Draw();
  this->graphPad[StripsOrientationType::ORIENTATION_HORIZONTAL]->SetGrid();
  this->graphPad[StripsOrientationType::ORIENTATION_HORIZONTAL]->cd();
  this->getHorizontalStripsMultiGraph()->Draw("APL*");

  this->getVerticalStripsMultiGraph()->Add( this->getVerticalStripsGraph());
  this->getVerticalStripsMultiGraph()->Add( this->getVerticalCalibratedStripsGraph());
  this->getVerticalStripsCanvas()->cd(2);
  this->graphPad[StripsOrientationType::ORIENTATION_VERTICAL] = dynamic_cast<TPad*>(this->getVerticalStripsCanvas()->GetPad(2));
  this->graphPad[StripsOrientationType::ORIENTATION_VERTICAL]->Draw();
  this->graphPad[StripsOrientationType::ORIENTATION_VERTICAL]->SetGrid();
  this->graphPad[StripsOrientationType::ORIENTATION_VERTICAL]->cd();
  this->getVerticalStripsMultiGraph()->Draw("APL*");

  TCanvas* canvas = this->ui->RootCanvas_ChannelGraph->getCanvas();
  canvas->cd();
  this->channelPad = new TPad("padChannel", "Grid", 0., 0., 1., 1.);
  this->channelPad->Draw();
  this->channelPad->SetGrid();
  this->channelPad->cd();
  this->graphChannel = new TGraph(1024);
  this->graphChannel->SetTitle("Channel data;Time (ms);Amplitude");
  this->graphChannel->Draw("AL*");

  this->linePedBegin = std::unique_ptr< TLine >(new TLine( 0., 0., 0., 1.));
  this->linePedBegin->SetVertical(kTRUE);
  this->linePedBegin->SetLineColor(kBlue);
  this->linePedBegin->SetLineStyle(7);
  this->linePedBegin->SetLineWidth(3.);
  this->linePedBegin->Draw();

  this->linePedEnd = std::unique_ptr< TLine >(new TLine( 0., 0., 0., 1.));
  this->linePedEnd->SetVertical(kTRUE);
  this->linePedEnd->SetLineColor(kBlue);
  this->linePedEnd->SetLineStyle(7);
  this->linePedEnd->SetLineWidth(3.);
  this->linePedEnd->Draw();

  this->lineSignalBegin = std::unique_ptr< TLine >(new TLine( 0., 0., 0., 1.));
  this->lineSignalBegin->SetVertical(kTRUE);
  this->lineSignalBegin->SetLineColor(kRed);
  this->lineSignalBegin->SetLineStyle(7);
  this->lineSignalBegin->SetLineWidth(3.);
  this->lineSignalBegin->Draw();

  this->lineSignalEnd = std::unique_ptr< TLine >(new TLine( 0., 0., 0., 1.));
  this->lineSignalEnd->SetVertical(kTRUE);
  this->lineSignalEnd->SetLineColor(kRed);
  this->lineSignalEnd->SetLineStyle(7);
  this->lineSignalEnd->SetLineWidth(3.);
  this->lineSignalEnd->Draw();

  canvas = this->ui->RootCanvas_ChannelHist->getCanvas();
  canvas->Divide(2, 1);
  canvas->cd(1);
  this->channelHistPad[ChannelSideType::SIDE_A] = dynamic_cast<TPad*>(canvas->GetPad(1));
  this->channelHistPad[ChannelSideType::SIDE_A]->Draw();
  this->channelHistPad[ChannelSideType::SIDE_A]->SetGrid();
  this->channelHistPad[ChannelSideType::SIDE_A]->cd();
  this->getChannelHistSideA()->Draw();
  this->getChannelHistSideA()->GetXaxis()->SetTitle("ADC");
  this->getChannelHistSideA()->GetYaxis()->SetTitle("Events");

  canvas->cd(2);
  this->channelHistPad[ChannelSideType::SIDE_B] = dynamic_cast<TPad*>(canvas->GetPad(2));
  this->channelHistPad[ChannelSideType::SIDE_B]->Draw();
  this->channelHistPad[ChannelSideType::SIDE_B]->SetGrid();
  this->channelHistPad[ChannelSideType::SIDE_B]->cd();
  this->getChannelHistSideB()->Draw();
  this->getChannelHistSideB()->GetXaxis()->SetTitle("ADC");
  this->getChannelHistSideB()->GetYaxis()->SetTitle("Events");

  canvas = this->ui->RootCanvas_Fit->getCanvas();
  canvas->Divide(1, 2);
  canvas->cd(1);
  this->padFit[StripsOrientationType::ORIENTATION_HORIZONTAL] = dynamic_cast<TPad*>(canvas->GetPad(1));
  this->padFit[StripsOrientationType::ORIENTATION_HORIZONTAL]->Draw();
  this->padFit[StripsOrientationType::ORIENTATION_HORIZONTAL]->SetGrid();
  this->padFit[StripsOrientationType::ORIENTATION_HORIZONTAL]->cd();
  this->graphFit[StripsOrientationType::ORIENTATION_HORIZONTAL]->Draw();
  this->graphFit[StripsOrientationType::ORIENTATION_HORIZONTAL]->SetTitle("Horizontal Strips (Vertical profile);mm;Mean charge (pC)");

  canvas->cd(2);
  this->padFit[StripsOrientationType::ORIENTATION_VERTICAL] = dynamic_cast<TPad*>(canvas->GetPad(2));
  this->padFit[StripsOrientationType::ORIENTATION_VERTICAL]->Draw();
  this->padFit[StripsOrientationType::ORIENTATION_VERTICAL]->SetGrid();
  this->padFit[StripsOrientationType::ORIENTATION_VERTICAL]->cd();
  this->graphFit[StripsOrientationType::ORIENTATION_VERTICAL]->Draw();
  this->graphFit[StripsOrientationType::ORIENTATION_VERTICAL]->SetTitle("Vertical Strips (Horizontal profile);mm;Mean charge (pC)");

  this->calibrationCanvas = this->ui->RootCanvas_CalibrationGraph->getCanvas();
  this->calibrationCanvas->cd();
  this->calibrationPad = new TPad("padCalibration", "Grid", 0., 0., 1., 1.);
  this->calibrationPad->Draw();
  this->calibrationPad->SetGrid();
  this->calibrationPad->cd();
  this->calibrationGraph = new TGraph(100);
  this->calibrationGraph->SetTitle("Counts;Offset (mV);Calibration");
  this->calibrationGraph->Draw("AL*");

  // Pseudo 2D Histogram
  this->pseudo2DCanvas = this->ui->RootCanvas_2D->getCanvas();
  this->pseudo2DCanvas->cd();
  this->pseudo2DPad = new TPad("padPseudo2D", "Grid", 0., 0., 1., 1.);
  this->pseudo2DPad->Draw();
  this->pseudo2DPad->SetGrid();
  this->pseudo2DPad->cd();
/*
  this->hist2D = new TH2F( "hist2D", "Pseudo 2D Distribution",
    4 * CHANNELS_PER_CHIP, 0., double(4 * CHANNELS_PER_CHIP),
    6 * CHANNELS_PER_CHIP, 0., double(6 * CHANNELS_PER_CHIP));
*/
  const int xBins = CHANNELS_PER_CHIP * 4;
  const Double_t* xBinsBorders = VerticalStripsBinsCorrect.data();
  for (size_t i = 0; i < VerticalStripsBinsCorrect.size(); ++i)
  {
    qDebug() << Q_FUNC_INFO << i << ' ' << VerticalStripsBinsCorrect[i];
  }
  this->hist2D = new TH2F( "hist2D", "Pseudo 2D Distribution", xBins, xBinsBorders, 6 * CHANNELS_PER_CHIP, 0., double(6 * CHANNELS_PER_CHIP));

  this->hist2D->Draw("COLZ");
  this->hist2D->GetXaxis()->SetTitle("Horizontal strips");
  this->hist2D->GetYaxis()->SetTitle("Vertical strips");

  connect( ui->PushButton_AcquisitionConnect, SIGNAL(clicked()), this, SLOT(onAcquisitionDeviceConnectClicked()));
  connect( ui->PushButton_AcquisitionDisconnect, SIGNAL(clicked()), this, SLOT(onAcquisitionDeviceDisconnectClicked()));
  connect( ui->PushButton_AgilentConnect, SIGNAL(clicked()), this, SLOT(onAgilentDeviceConnectClicked()));
  connect( ui->PushButton_AgilentDisconnect, SIGNAL(clicked()), this, SLOT(onAgilentDeviceDisconnectClicked()));
  connect( ui->PushButton_SetAmplitude, SIGNAL(clicked()), this, SLOT(onSetAmplitudeClicked()));
  connect( ui->PushButton_SetOffset, SIGNAL(clicked()), this, SLOT(onSetOffsetClicked()));
  connect( ui->PushButton_SetFrequency, SIGNAL(clicked()), this, SLOT(onSetFrequencyClicked()));
  connect( ui->PushButton_SetDutyCycle, SIGNAL(clicked()), this, SLOT(onSetDutyCycleClicked()));
  connect( ui->PushButton_AgilentSendCommand, SIGNAL(clicked()), this, SLOT(onSendCommandClicked()));
  connect( ui->PushButton_StartIterations, SIGNAL(clicked()), this, SLOT(onStartIterationAcquisitionClicked()));
  connect( ui->PushButton_Calibration, SIGNAL(clicked()), this, SLOT(onCalibrationClicked()));

  connect( ui->PushButton_ChipReset, SIGNAL(clicked()), this, SLOT(onChipResetClicked()));
  connect( ui->PushButton_Acquisition, SIGNAL(clicked()), this, SLOT(onAcquisitionClicked()));
  connect( ui->PushButton_ExternalStartSingleShot, SIGNAL(clicked()), this, SLOT(onSingleShotClicked()));
  connect( ui->PushButton_ExternalStart, SIGNAL(clicked()), this, SLOT(onExternalStartClicked()));
  connect( ui->PushButton_AlteraReset, SIGNAL(clicked()), this, SLOT(onAlteraResetClicked()));
  connect( ui->PushButton_WriteCapacities, SIGNAL(clicked()), this, SLOT(onWriteCapacitiesClicked()));
  connect( ui->PushButton_SetIntegrationTime, SIGNAL(clicked()), this, SLOT(onSetIntegrationTimeClicked()));
  connect( ui->PushButton_SetCapacity, SIGNAL(clicked()), this, SLOT(onSetCapacityClicked()));
  connect( ui->PushButton_SetSamples, SIGNAL(clicked()), this, SLOT(onSetSamplesClicked()));
  connect( ui->PushButton_SetDevices, SIGNAL(clicked()), this, SLOT(onSetNumberOfChipsClicked()));
  connect( ui->PushButton_AdcResolutionSet, SIGNAL(clicked()), this, SLOT(onAdcResolutionSetClicked()));
  connect( ui->PushButton_InitiateDevices, SIGNAL(clicked()), this, SLOT(onInitiateDevicesClicked()));
  connect( ui->PushButton_SingleCharSymbol, SIGNAL(clicked()), this, SLOT(onFirstConnectResponce()));
  connect( ui->PushButton_DevicesEnabled, SIGNAL(clicked()), this, SLOT(onSetDevicesEnabled()));
  connect( ui->PushButton_ClearHistograms, SIGNAL(clicked()), this, SLOT(onClearHistogramsClicked()));

  connect( ui->PushButton_ProcessRawData, SIGNAL(clicked()), this, SLOT(onProcessRawDataClicked()));

  connect( ui->PushButton_UpdateChannelGraph, SIGNAL(clicked()), this, SLOT(onUpdateChannelGraphClicked()));
  connect( ui->PushButton_ProcessCounts, SIGNAL(clicked()), this, SLOT(onProcessSpillChannelsCountsClicked()));
  connect( ui->SpinBox_PedBegin, SIGNAL(valueChanged(int)), this, SLOT(onPedestalsBeginClicked(int)));
  connect( ui->SpinBox_PedEnd, SIGNAL(valueChanged(int)), this, SLOT(onPedestalsEndClicked(int)));
  connect( ui->SpinBox_SignalBegin, SIGNAL(valueChanged(int)), this, SLOT(onSignalBeginClicked(int)));
  connect( ui->SpinBox_SignalEnd, SIGNAL(valueChanged(int)), this, SLOT(onSignalEndClicked(int)));
  connect( ui->PushButton_OpenFile, SIGNAL(clicked()), this, SLOT(onOpenRootFileClicked()));
  connect( ui->PushButton_ClearList, SIGNAL(clicked()), this, SLOT(onClearSpillListClicked()));
  connect( ui->PushButton_ProcessSpills, SIGNAL(clicked()), this, SLOT(onProcessSelectedItemsClicked()));
  connect( ui->PushButton_Fit, SIGNAL(clicked()), this, SLOT(onFitParametersClicked()));
  connect( ui->PushButton_TanCalculation, SIGNAL(clicked()), this, SLOT(onTangentCalculationClicked()));
  connect( ui->PushButton_Calibrate, SIGNAL(clicked()), this, SLOT(onCalibrateClicked()));

  connect( ui->ButtonGroup_AdcMode, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onAcquisitionAdcModeResolutionChanged(QAbstractButton*)));
  connect( ui->ButtonGroup_SelectedCamera, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onCameraNumberChanged(QAbstractButton*)));

  connect( timer, SIGNAL(timeout()), this, SLOT(onRootEventsTimeout())); // iterate ROOT events
  connect( spillTimeoutTimer, SIGNAL(timeout()), this, SLOT(onSpillTimeout())); // iterate spill timeout
  connect( initiationTimer, SIGNAL(timeout()), this, SLOT(onFirstConnectResponce())); // first responce timeout

#ifndef DEBUG
  this->ui->PushButton_ProcessRawData->hide();
  this->ui->PushButton_SingleCharSymbol->hide();
  this->ui->PushButton_Calibrate->hide();
#endif

  for (int i = 0; i < CHIPS_PER_PLANE * 2; ++i)
  {
    connect( this->CheckBox_DevicesEnabled[i], SIGNAL(toggled(bool)), this, SLOT(onDeviceEnabledCheckBoxChecked(bool)));
  }
  connect( this->ui->CheckBox_AllDevicesEnabled, SIGNAL(toggled(bool)), this, SLOT(onAllDevicesEnabledChecked(bool)));

  this->timer->start(20);
  this->spillTimeoutTimer->setInterval(200);
  this->initiationTimer->setInterval(1000);
  loadSettings();
  loadICSettings();
}

MainWindow::~MainWindow()
{
  if (this->initiationProgress)
  {
    this->initiationProgress->hide();
    delete this->initiationProgress;
    this->initiationProgress = nullptr;
  }

  if (rootFile)
  {
    rootFile->Close();
    delete rootFile;
    rootFile = nullptr;
  }
  timer->stop();
  saveSettings();

  delete this->histChannel[ChannelSideType::SIDE_A];
  delete this->histChannel[ChannelSideType::SIDE_B];
  this->histChannel[ChannelSideType::SIDE_A] = nullptr;
  this->histChannel[ChannelSideType::SIDE_B] = nullptr;

  this->channelHistPad[ChannelSideType::SIDE_A] = nullptr;
  this->channelHistPad[ChannelSideType::SIDE_B] = nullptr;

  delete this->graphChannel;
  this->graphChannel = nullptr;
  delete this->channelPad;
  this->channelPad = nullptr;

  this->graphPad[StripsOrientationType::ORIENTATION_VERTICAL] = nullptr;
  this->graphPad[StripsOrientationType::ORIENTATION_HORIZONTAL] = nullptr;
  this->hist2Pad[StripsOrientationType::ORIENTATION_HORIZONTAL] = nullptr;
  this->hist2Pad[StripsOrientationType::ORIENTATION_VERTICAL] = nullptr;

  delete this->hist2Strips[StripsOrientationType::ORIENTATION_HORIZONTAL];
  this->hist2Strips[StripsOrientationType::ORIENTATION_HORIZONTAL] = nullptr;
  delete this->hist2Strips[StripsOrientationType::ORIENTATION_VERTICAL];
  this->hist2Strips[StripsOrientationType::ORIENTATION_VERTICAL] = nullptr;
  delete this->graphStrips[StripsOrientationType::ORIENTATION_HORIZONTAL];
  this->graphStrips[StripsOrientationType::ORIENTATION_HORIZONTAL] = nullptr;
  delete this->graphStrips[StripsOrientationType::ORIENTATION_VERTICAL];
  this->graphStrips[StripsOrientationType::ORIENTATION_VERTICAL] = nullptr;

  this->rootCanvas[StripsOrientationType::ORIENTATION_HORIZONTAL] = nullptr;
  this->rootCanvas[StripsOrientationType::ORIENTATION_VERTICAL] = nullptr;

  delete this->graphFit[StripsOrientationType::ORIENTATION_HORIZONTAL];
  this->graphFit[StripsOrientationType::ORIENTATION_HORIZONTAL] = nullptr;
  delete this->graphFit[StripsOrientationType::ORIENTATION_VERTICAL];
  this->graphFit[StripsOrientationType::ORIENTATION_VERTICAL] = nullptr;

  delete this->calibrationGraph;
  this->calibrationGraph = nullptr;
  delete this->calibrationPad;
  this->calibrationPad = nullptr;

  delete this->hist2D;
  this->hist2D = nullptr;
  delete this->pseudo2DPad;
  this->pseudo2DPad = nullptr;

  delete ui;
}

/**
 * @brief MainWindow::onRootEventsTimeout
 * Iterate ROOT events
 */
void MainWindow::onRootEventsTimeout()
{
  // call the inner loop of ROOT
  gSystem->ProcessEvents();
}

void MainWindow::onSpillTimeout()
{
  auto timeCurrent = std::chrono::steady_clock::now();
  std::chrono::duration< float, std::milli > spillDuration(timeCurrent - timeWaitingBegin);
  this->ui->Label_LastSpillTimeout->setText(tr("%1 ms").arg(spillDuration.count()));
}

void MainWindow::onAcquisitionDeviceConnectClicked()
{
  QString name = ui->LineEdit_AcquisitionDeviceName->text();
  QString dataName = ui->LineEdit_DataDeviceName->text();
  this->acquisitionPort = new QSerialPort(name, this);
  this->acquisitionDataPort = new QSerialPort(dataName, this);

  bool connected = false;
  if (this->acquisitionPort && this->acquisitionPort->open(QIODevice::ReadWrite))
  {
    this->spillNumber = 0;
    this->lastCommandWritten.clear();
    this->acquisitionResponseBuffer.clear();

    this->acquisitionPort->setBaudRate(QSerialPort::Baud57600);
    this->acquisitionPort->setDataBits(QSerialPort::Data8);
    this->acquisitionPort->setParity(QSerialPort::NoParity);
    this->acquisitionPort->setStopBits(QSerialPort::OneStop);
    this->acquisitionPort->setFlowControl(QSerialPort::NoFlowControl);

    connect(this->acquisitionPort, SIGNAL(readyRead()), this, SLOT(acquisitionSerialPortDataReady()));
    connect(this->acquisitionPort, SIGNAL(bytesWritten(qint64)), this, SLOT(acquisitionSerialPortBytesWritten(qint64)));
    connect(this->acquisitionPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(acquisitionSerialPortError(QSerialPort::SerialPortError)));

    ui->PushButton_AcquisitionConnect->setEnabled(false);
    ui->PushButton_AcquisitionDisconnect->setEnabled(true);
/*
    bool res = ui->CheckBox_ExternalStart->blockSignals(true);
    ui->CheckBox_ExternalStart->setChecked(false);
    res = ui->CheckBox_ExternalStart->blockSignals(false);
*/
    ui->statusbar->showMessage(QObject::tr("Acquisition device connected"), 1000);
//    QTimer::singleShot(0, this, SLOT(onAcquisitionGetClicked()));
    int run = this->ui->SpinBox_RunNumber->value();
    QDateTime dateTime = QDateTime::currentDateTime();
    std::stringstream sstream;
    int cameraNumber = this->currentCameraNumber();
    sstream << "ROOT_" << run << "_IC0" << cameraNumber << '_' << dateTime.toString("ddMMyyyy_hhmmss").toStdString() << ".root";
    std::string name = sstream.str();
    if (rootFile)
    {
      rootFile->Close();
      delete rootFile;
      rootFile = nullptr;
    }
    rootFile = new TFile(name.c_str(), "RECREATE");
/*
    // disable external start
    unsigned char buf[2] = { 'A', 0 };
    QByteArray setAcquisitionCommand( reinterpret_cast<char*>(buf), 2);
    if (this->acquisitionPort && this->acquisitionPort->isOpen())
    {
      this->acquisitionPort->write(setAcquisitionCommand);
    }
*/
    this->ui->RadioButton_Camera1->setEnabled(false);
    this->ui->RadioButton_Camera2->setEnabled(false);
    this->initiationProgress->setLabelText("Reset ATmega128A input command buffer...");
    this->initiationProgress->setRange(0, 0);
    this->initiationProgress->setValue(0);
    this->initiationProgress->show();
    this->initiationTimer->start();
    connected = true;
  }
  else if (this->acquisitionPort && !this->acquisitionPort->isOpen())
  {
    QMessageBox msgBox(this);
    msgBox.setModal(true);
    msgBox.setWindowTitle(tr("IC control"));
    msgBox.setText(tr("Unable to connect device %1.\n%2.").arg(this->acquisitionPort->portName()).arg(this->acquisitionPort->errorString()));
    msgBox.exec();
    ui->statusbar->showMessage(QObject::tr("Unable to connect device"), 1000);

    this->ui->RadioButton_Camera1->setEnabled(true);
    this->ui->RadioButton_Camera2->setEnabled(true);

    delete this->acquisitionPort;
    this->acquisitionPort = nullptr;
  }

  if (this->acquisitionDataPort && this->acquisitionDataPort->open(QIODevice::ReadOnly))
  {
    qDebug() << Q_FUNC_INFO << ": 0K.";
    this->acquisitionDataPort->setBaudRate(QSerialPort::Baud57600);
    this->acquisitionDataPort->setDataBits(QSerialPort::Data8);
    this->acquisitionDataPort->setParity(QSerialPort::NoParity);
    this->acquisitionDataPort->setStopBits(QSerialPort::OneStop);
    this->acquisitionDataPort->setFlowControl(QSerialPort::NoFlowControl);

    connect(this->acquisitionDataPort, SIGNAL(readyRead()), this, SLOT(acquisitionDataPortDataReady()));
    connect(this->acquisitionDataPort, SIGNAL(bytesWritten(qint64)), this, SLOT(acquisitionDataPortBytesWritten(qint64)));
    connect(this->acquisitionDataPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(acquisitionDataPortError(QSerialPort::SerialPortError)));
  }
  else if (this->acquisitionDataPort && !this->acquisitionDataPort->isOpen())
  {
      QMessageBox msgBox(this);
      msgBox.setModal(true);
      msgBox.setWindowTitle(tr("IC control"));
      msgBox.setText(tr("Unable to connect device %1.\n%2.").arg(this->acquisitionDataPort->portName()).arg(this->acquisitionDataPort->errorString()));
      msgBox.exec();
      ui->statusbar->showMessage(QObject::tr("Unable to connect device"), 1000);

    delete this->acquisitionDataPort;
    this->acquisitionDataPort = nullptr;
  }

  this->ui->PushButton_AlteraReset->setEnabled(connected);
  this->ui->PushButton_SetDevices->setEnabled(connected);
  this->ui->PushButton_DevicesEnabled->setEnabled(connected);
  this->ui->PushButton_SetFrequency->setEnabled(connected);
  this->ui->PushButton_SetCapacity->setEnabled(connected);
  this->ui->PushButton_SetIntegrationTime->setEnabled(connected);
  this->ui->PushButton_SetSamples->setEnabled(connected);
  this->ui->PushButton_ExternalStart->setEnabled(connected);
  this->ui->PushButton_ExternalStartSingleShot->setEnabled(connected);
  this->ui->PushButton_AdcResolutionSet->setEnabled(connected);
  this->ui->PushButton_WriteCapacities->setEnabled(connected);
  this->ui->PushButton_Acquisition->setEnabled(connected);
  this->ui->PushButton_ChipReset->setEnabled(connected);
  this->ui->PushButton_InitiateDevices->setEnabled(connected);
  this->ui->PushButton_StartIterations->setEnabled(connected);
}

void MainWindow::onAcquisitionDeviceDisconnectClicked()
{
  bool connected = true;
  if (this->acquisitionPort && this->acquisitionPort->isOpen())
  {
    this->acquisitionPort->flush();
    this->acquisitionPort->close();
    delete this->acquisitionPort;
    this->acquisitionPort = nullptr;
  }
  else if (this->acquisitionPort && !this->acquisitionPort->isOpen())
  {
    delete this->acquisitionPort;
    this->acquisitionPort = nullptr;
  }

  if (this->acquisitionDataPort && this->acquisitionDataPort->isOpen())
  {
    this->acquisitionDataPort->flush();
    this->acquisitionDataPort->close();
    delete this->acquisitionDataPort;
    this->acquisitionDataPort = nullptr;
  }
  else if (this->acquisitionDataPort && !this->acquisitionDataPort->isOpen())
  {
    delete this->acquisitionDataPort;
    this->acquisitionDataPort = nullptr;
  }
  connected = false;

  if (rootFile)
  {
    rootFile->Close();
    delete rootFile;
    rootFile = nullptr;
  }

  ui->PushButton_AcquisitionConnect->setEnabled(true);
  ui->PushButton_AcquisitionDisconnect->setEnabled(false);
  int run = this->ui->SpinBox_RunNumber->value();
  this->ui->SpinBox_RunNumber->setValue(++run);

  this->ui->PushButton_AlteraReset->setEnabled(connected);
  this->ui->PushButton_SetDevices->setEnabled(connected);
  this->ui->PushButton_DevicesEnabled->setEnabled(connected);
  this->ui->PushButton_SetFrequency->setEnabled(connected);
  this->ui->PushButton_SetCapacity->setEnabled(connected);
  this->ui->PushButton_SetIntegrationTime->setEnabled(connected);
  this->ui->PushButton_SetSamples->setEnabled(connected);
  this->ui->PushButton_ExternalStart->setEnabled(connected);
  this->ui->PushButton_ExternalStartSingleShot->setEnabled(connected);
  this->ui->PushButton_AdcResolutionSet->setEnabled(connected);
  this->ui->PushButton_WriteCapacities->setEnabled(connected);
  this->ui->PushButton_Acquisition->setEnabled(connected);
  this->ui->PushButton_ChipReset->setEnabled(connected);
  this->ui->PushButton_InitiateDevices->setEnabled(connected);
  this->ui->PushButton_StartIterations->setEnabled(connected);

  this->ui->RadioButton_Camera1->setEnabled(true);
  this->ui->RadioButton_Camera2->setEnabled(true);

  this->spillTimeoutTimer->stop();
  this->ui->Label_LastSpillTimeout->setText("");

  ui->statusbar->showMessage(QObject::tr("Acquisition device disconnected"), 1000);
  QApplication::restoreOverrideCursor();
}

void MainWindow::acquisitionSerialPortBytesWritten(qint64 bytes)
{
  qDebug() << Q_FUNC_INFO << "Serial port data written bytes: " << bytes;
  if (this->initiateDevicesCommandsList.size() && this->lastCommandWritten.size() == bytes)
  {
    this->initiateDevicesCommandsList.pop_front();
    if (this->initiationProgress->isVisible())
    {
      this->initiationProgress->setValue(this->initiateDevicesCommandsList.size());
    }
//    QApplication::setOverrideCursor(Qt::WaitCursor);
  }
  if (this->lastCommandWritten.size() == bytes && this->lastCommandWritten == AcquisitionCommand)
  {
    qDebug() << Q_FUNC_INFO << "Acquisition command has been written";
  }
  else if (this->lastCommandWritten.size() == bytes && this->lastCommandWritten == SingleShotCommand)
  {
//    QApplication::setOverrideCursor(Qt::WaitCursor);
    timeWaitingBegin = std::chrono::steady_clock::now();
    this->spillTimeoutTimer->start();
    qDebug() << Q_FUNC_INFO << "Single shot command has been written, waiting for external start";
  }
}

void MainWindow::acquisitionDataPortBytesWritten(qint64 bytes)
{
  qDebug() << Q_FUNC_INFO << "Serial port data written bytes: " << bytes;
}

void MainWindow::acquisitionSerialPortDataReady()
{
  QByteArray portData = this->acquisitionPort->readAll();

//  qDebug() << Q_FUNC_INFO << "Data recieved: " << portData.size();

  if (this->initiateDevicesCommandsList.isEmpty() && this->initiationProgress->isVisible())
  {
    QApplication::restoreOverrideCursor();
    this->initiationProgress->close();
  }

  this->acquisitionResponseBuffer.push_back(portData);
  const QByteArray& data = this->acquisitionResponseBuffer;

  if (this->acquisitionResponseBuffer.size() == 4 && this->checkLastCommandWrittenAndRespose())
  {
    qDebug() << Q_FUNC_INFO << this->acquisitionResponseBuffer;
    switch (data[0])
    {
    case 'A':
      chamberResponse.ExternalStartState = bool(data[1] - '0');
      qDebug() << Q_FUNC_INFO << "Set external interrupt command response: " << chamberResponse.ExternalStartState;
      this->ui->statusbar->showMessage( tr("External interrupt is set, value: %1").arg(chamberResponse.ExternalStartState), 3000);
      if (this->lastCommandWritten.size() == 1 && this->lastCommandWritten.startsWith('A'))
      {
          this->acquisitionResponseBuffer.clear();
          this->lastCommandWritten.clear();
          this->initiateDevicesCommandsList.clear();
          QApplication::restoreOverrideCursor();

          if (this->initiationProgress->isVisible())
          {
            this->initiationProgress->hide();
            this->initiationProgress->close();
          }
          this->initiationTimer->stop();
          return;
      }
      break;
    case 'D':
      chamberResponse.AdcMode = (data[1] - '0') ? 20 : 16;
      qDebug() << Q_FUNC_INFO << "ADC resolution command response: " << chamberResponse.AdcMode;
      this->ui->statusbar->showMessage( tr("ADC resolution is %1-bit").arg(chamberResponse.AdcMode), 3000);
      break;
    case 'G':
      qCritical() << Q_FUNC_INFO << "Capasities have been written into chip";
      this->ui->statusbar->showMessage( tr("Capasities have been written into chip"), 3000);
      break;
    case 'I':
      qDebug() << Q_FUNC_INFO << "Set integration time command response: " << char(data[1]);
      chamberResponse.IntegrationTimeCode = (data[1] - 'A');
      this->ui->statusbar->showMessage( tr("Integration time is %1 ms").arg((chamberResponse.IntegrationTimeCode + 1) * 2), 3000);
      break;
    case 'M':
      chamberResponse.ChipsEnabled = data[1] - 'A';
      qDebug() << Q_FUNC_INFO << "Number of chips enabled: " << chamberResponse.ChipsEnabled;
      this->ui->statusbar->showMessage( tr("Number of chips enabled: %1").arg(chamberResponse.ChipsEnabled), 3000);
      break;
    case 'O':
      qDebug() << Q_FUNC_INFO << "Set number of chips command response: " << char(data[1]);
      this->ui->statusbar->showMessage( tr("Number of chips (must be 12): %1").arg(data[1] - 'A'), 3000);
      break;
    default:
      break;
    }
    this->acquisitionResponseBuffer.clear();
    this->lastCommandWritten.clear();
    if (this->initiateDevicesCommandsList.size())
    {
      QTimer::singleShot( 100, this, SLOT(writeNextCommandFromInitiationList()));
    }
    else
    {
      QApplication::restoreOverrideCursor();
    }
    return;
  }
  else if (this->acquisitionResponseBuffer.size() == 4 && !this->checkLastCommandWrittenAndRespose())
  {
    qCritical() << Q_FUNC_INFO << "Wrong or strange response: " << this->acquisitionResponseBuffer;
    this->acquisitionResponseBuffer.clear();
    this->lastCommandWritten.clear();
    QApplication::restoreOverrideCursor();
    if (this->initiateDevicesCommandsList.size())
    {
      QTimer::singleShot( 100, this, SLOT(writeNextCommandFromInitiationList()));
    }
    return;
  }

  if (this->acquisitionResponseBuffer.startsWith('C') && this->acquisitionResponseBuffer.size() == 4 && this->checkLastCommandWrittenAndRespose())
  {
    qDebug() << Q_FUNC_INFO << this->acquisitionResponseBuffer;

    int capacity = data[1] - '0';
    if (capacity >= 0)
    {
      qDebug() << Q_FUNC_INFO << "Set chip capacity command response: " << capacity;
      chamberResponse.CapacityCode = capacity;
      this->ui->statusbar->showMessage( tr("Capacity is %2").arg(capacity), 3000);
    }
    this->acquisitionResponseBuffer.clear();
    this->lastCommandWritten.clear();
    QApplication::restoreOverrideCursor();
    if (this->initiateDevicesCommandsList.size())
    {
      QTimer::singleShot( 100, this, SLOT(writeNextCommandFromInitiationList()));
    }
    return;
  }
  else if (this->acquisitionResponseBuffer.startsWith('C') && this->acquisitionResponseBuffer.size() == 4 && !this->checkLastCommandWrittenAndRespose())
  {
    qCritical() << Q_FUNC_INFO << "Wrong or strange chip capacity command response: " << this->acquisitionResponseBuffer;
    this->ui->statusbar->showMessage( tr("Wrong or strange chip capacity command response"), 3000);
    this->acquisitionResponseBuffer.clear();
    this->lastCommandWritten.clear();
    QApplication::restoreOverrideCursor();
    if (this->initiateDevicesCommandsList.size())
    {
      QTimer::singleShot( 100, this, SLOT(writeNextCommandFromInitiationList()));
    }
    return;
  }

  if (this->acquisitionResponseBuffer.size() == 3 && this->checkLastCommandWrittenAndRespose())
  {
    qDebug() << Q_FUNC_INFO << this->acquisitionResponseBuffer;
    switch (data[0])
    {
    case 'G':
      QApplication::restoreOverrideCursor();
      qDebug() << Q_FUNC_INFO << "DDC232 configuration register is set";
      this->ui->statusbar->showMessage( tr("DDC232 configuration register is set"), 3000);
      break;
    case 'R':
      QApplication::restoreOverrideCursor();
      qDebug() << Q_FUNC_INFO << "ALTERA reset";
      this->ui->statusbar->showMessage( tr("ALTERA reset"), 3000);
      break;
    case 'H':
      QApplication::restoreOverrideCursor();
      qDebug() << Q_FUNC_INFO << "Chip reset";
      this->ui->statusbar->showMessage( tr("Chip reset"), 3000);
      break;
    case 'S':
      QApplication::restoreOverrideCursor();
      qDebug() << Q_FUNC_INFO << "Single shot acquisition with external start";
      this->ui->statusbar->showMessage( tr("Single shot"), 3000);
      break;
    case 'E':
      QApplication::restoreOverrideCursor();
      qDebug() << Q_FUNC_INFO << "Devices enabled are set";
      this->ui->statusbar->showMessage( tr("Devices enabled are set"), 3000);
      break;
    case 'P':
      QApplication::restoreOverrideCursor();
      qDebug() << Q_FUNC_INFO << "New number of samples are set";
      this->ui->statusbar->showMessage( tr("New number of samples are set"), 3000);
      break;
    default:
      QApplication::restoreOverrideCursor();
      break;
    }
    this->acquisitionResponseBuffer.clear();
    this->lastCommandWritten.clear();
    if (this->initiateDevicesCommandsList.size())
    {
      QTimer::singleShot( 100, this, SLOT(writeNextCommandFromInitiationList()));
    }
    return;
  }
  else if (this->acquisitionResponseBuffer.size() == 3 && !this->checkLastCommandWrittenAndRespose())
  {
    qCritical() << Q_FUNC_INFO << "Wrong or strange response: " << this->acquisitionResponseBuffer;
    this->acquisitionResponseBuffer.clear();
    this->lastCommandWritten.clear();
    QApplication::restoreOverrideCursor();
    if (this->initiateDevicesCommandsList.size())
    {
      QTimer::singleShot( 100, this, SLOT(writeNextCommandFromInitiationList()));
    }
    return;
  }

  if (this->acquisitionResponseBuffer.startsWith("Start") && this->acquisitionResponseBuffer.size() == 5)
  {
    QApplication::setOverrideCursor(Qt::WaitCursor);
    timeWaitingBegin = std::chrono::steady_clock::now();
    this->spillTimeoutTimer->start();
  }
  if (this->acquisitionResponseBuffer.startsWith("Start") && this->acquisitionResponseBuffer.endsWith("Finish"))
  {
    qDebug() << Q_FUNC_INFO << "DATA SIZE: " << this->acquisitionDataBuffer.size();
    QApplication::restoreOverrideCursor();

    chamberResponse.ChipsEnabledCode = this->devicesEnabled();

    timeWaitingEnd = std::chrono::steady_clock::now();

    /// Save raw spill data
    QDateTime dateTime = QDateTime::currentDateTime();
    this->onProcessRawDataClicked();
    this->storeSpillData(dateTime);
    /// Data is safe => clear acquisition buffer
    this->acquisitionDataBuffer.clear();
    std::bitset< CHIPS_PER_PLANE * 2 > chipsDevices(chamberResponse.ChipsEnabledCode);
    if (chipsDevices.count() == this->chipsAddresses.size())
    {
      /// Save processed data
      this->onProcessSpillChannelsCountsClicked();
      this->hist2Pad[ORIENTATION_VERTICAL]->Modified();
      this->hist2Pad[ORIENTATION_VERTICAL]->Update();
      this->graphPad[ORIENTATION_VERTICAL]->Modified();
      this->graphPad[ORIENTATION_VERTICAL]->Update();
      this->hist2Pad[ORIENTATION_HORIZONTAL]->Modified();
      this->hist2Pad[ORIENTATION_HORIZONTAL]->Update();
      this->graphPad[ORIENTATION_HORIZONTAL]->Modified();
      this->graphPad[ORIENTATION_HORIZONTAL]->Update();
    }
    this->acquisitionResponseBuffer.clear();
    this->lastCommandWritten.clear();
    std::chrono::duration< float > acquisitionTime(timeWaitingEnd - timeWaitingBegin);
    auto timeCurrent = std::chrono::steady_clock::now();
    std::chrono::duration< float > processingTime(timeCurrent - timeWaitingEnd);
    this->ui->statusbar->showMessage(tr("Last spill acquisition time: %1 seconds, processing time: %2 seconds").arg(acquisitionTime.count()).arg(processingTime.count()), 3000);
    QApplication::restoreOverrideCursor();

    if (this->initiateDevicesCommandsList.size())
    {
      QTimer::singleShot( 100, this, SLOT(writeNextCommandFromInitiationList()));
    }
    if (this->calibrationEnabled)
    {
      auto calibrationIter = this->calibrationChannelsCounts.end();
      calibrationIter--;
//      this->calibrationChannelsCounts[calibrationIter->first] = this->channelsCounts[0];
      QTimer::singleShot( 100, this, SLOT(onSetNextOffset()));
    }
    return;
  }
  if (this->acquisitionResponseBuffer.startsWith('L') && this->acquisitionResponseBuffer.size() == 15 && this->checkLastCommandWrittenAndRespose())
  {
    qDebug() << Q_FUNC_INFO << this->acquisitionResponseBuffer;

    {
      qDebug() << Q_FUNC_INFO << "List of enabled chips is recieved";
      this->ui->statusbar->showMessage( tr("List of enabled chips is recieved"), 3000);
    }
    this->acquisitionResponseBuffer.clear();
    this->lastCommandWritten.clear();
    QApplication::restoreOverrideCursor();
    if (this->initiateDevicesCommandsList.size())
    {
      QTimer::singleShot( 100, this, SLOT(writeNextCommandFromInitiationList()));
    }
    return;
  }

  if (this->acquisitionResponseBuffer.startsWith("Start") && this->acquisitionResponseBuffer.contains("Abort"))
  {
    int restIndexOf = this->acquisitionResponseBuffer.indexOf("Abort") + std::strlen("Abort");
    QByteArray restResponse = this->acquisitionResponseBuffer.mid(restIndexOf);
    qCritical() << Q_FUNC_INFO << "Abort found! Rest response: " << restResponse;
    // Parse rest response
    // if response is OK
    if (checkLastCommandWrittenAndRespose(restResponse))
    {
      this->lastCommandWritten.clear();
      this->acquisitionResponseBuffer.clear();
      std::chrono::duration< float > acquisitionTime(timeWaitingEnd - timeWaitingBegin);
      this->ui->statusbar->showMessage(tr("Acquisition abort time: %1 seconds").arg(acquisitionTime.count()), 1000);
      QApplication::restoreOverrideCursor();
    }
    else
    {
      this->acquisitionResponseBuffer = restResponse;
      std::chrono::duration< float > acquisitionTime(timeWaitingEnd - timeWaitingBegin);
      this->ui->statusbar->showMessage(tr("Acquisition abort time: %1 seconds").arg(acquisitionTime.count()), 1000);
      QApplication::restoreOverrideCursor();
      QTimer::singleShot( 100, this, SLOT(writeLastCommandOnceAgain()));
    }
    return;
  }
  if (this->acquisitionResponseBuffer.startsWith("Welcome") && this->acquisitionResponseBuffer.size() == std::strlen("Welcome"))
  {
      this->acquisitionResponseBuffer.clear();
      this->lastCommandWritten.clear();
      this->initiateDevicesCommandsList.clear();
      QApplication::restoreOverrideCursor();

      if (this->initiationProgress->isVisible())
      {
        this->initiationProgress->close();
      }
      this->initiationTimer->stop();
  }
}

void MainWindow::acquisitionSerialPortError(QSerialPort::SerialPortError)
{
}

void MainWindow::acquisitionDataPortDataReady()
{
  if (!this->acquisitionDataPort)
  {
    return;
  }
  QByteArray portData = this->acquisitionDataPort->readAll();
  this->acquisitionDataBuffer.push_back(portData);
//  qDebug() << Q_FUNC_INFO << "BUFFER DATA SIZE: " << this->acquisitionDataBuffer.size();
}

void MainWindow::acquisitionDataPortError(QSerialPort::SerialPortError)
{
}

void MainWindow::onProcessRawDataClicked()
{
  this->channelsCountsA.clear();
  this->channelsCountsB.clear();

//  unsigned char* data = reinterpret_cast<unsigned char*>(this->acquisitionDataBuffer.data());

  std::ofstream file("data.txt");
  const QByteArray& arr = this->acquisitionDataBuffer;
  std::array< int, 4 > findData{ 0 , 0 , 0 , 0 };
  for (int i = 0; i < arr.size() - 4; i += 4)
  {
    std::bitset< CHAR_BIT > d0(arr.at(i)), d1(arr.at(i + 1)), d2(arr.at(i + 2)), d3(arr.at(i + 3));
    if (!d0.test(7) && d0.test(0))
    {
      findData[0] += 1;
    }
    if (!d1.test(7) && d1.test(0))
    {
      findData[1] += 1;
    }
    if (!d2.test(7) && d2.test(0))
    {
      findData[2] += 1;
    }
    if (!d3.test(7) && d3.test(0))
    {
      findData[3] += 1;
    }
  }
  std::array< int, 4 >::iterator findDataIter = std::max_element( findData.begin(), findData.end());
  int offset = findDataIter - findData.begin();
  qDebug() << "FindData: " << findData[0] << ' ' << findData[1] << ' ' << findData[2] << ' ' << findData[3] << ' ' << offset;

  for (int i = offset; i < arr.size() - 4; i += 4)
  {
    std::bitset< CHAR_BIT > d0(arr.at(i)), d1(arr.at(i + 1)), d2(arr.at(i + 2)), d3(arr.at(i + 3));
    file << d0.to_string() << ' ' << d1.to_string() << ' ' << d2.to_string() << ' ' << d3.to_string() << '\n';
  }
  file.close();

  constexpr int SIDE_BIT = 6;
  constexpr int CHIP_BITS = 4;
  this->chipsAddresses.clear();
  for (int i = offset; i < arr.size(); i += 4)
  {
    std::bitset< CHAR_BIT > d0(arr.at(i)), d1(arr.at(i + 1)), d2(arr.at(i + 2)), d3(arr.at(i + 3));
    ReverseBits< CHAR_BIT >(d0);
    int side = d0.test(SIDE_BIT);
    int channel = static_cast<int>(((d0 >> 1) & std::bitset< CHAR_BIT >(0x1F)).to_ulong());
    std::bitset< CHIP_BITS > chipBits((d1 >> CHIP_BITS).to_ulong());
    ReverseBits< CHIP_BITS >(chipBits);
    int chip = chipBits.to_ulong() - CHIP_BITS;
    this->chipsAddresses.push_back(chip);
    std::array< std::vector< int >, CHANNELS_PER_CHIP >& channelsA = this->channelsCountsA[chip];
    std::array< std::vector< int >, CHANNELS_PER_CHIP >& channelsB = this->channelsCountsB[chip];
    std::vector< int >& channelVectorA = channelsA[channel];
    std::vector< int >& channelVectorB = channelsB[channel];
    ReverseBits< CHAR_BIT >(d2);
    ReverseBits< CHAR_BIT >(d3);
    int count = static_cast< int >((d3.to_ulong() << CHAR_BIT) | d2.to_ulong());
    if (side)
    {
      channelVectorA.push_back(count);
    }
    else
    {
      channelVectorB.push_back(count);
    }
  }

  std::vector< int >::iterator last = std::unique(this->chipsAddresses.begin(), this->chipsAddresses.end());
  this->chipsAddresses.erase(last, this->chipsAddresses.end());
  std::sort(this->chipsAddresses.begin(), this->chipsAddresses.end());
  last = std::unique(this->chipsAddresses.begin(), this->chipsAddresses.end());
  this->chipsAddresses.erase(last, this->chipsAddresses.end());

  QString chipsStr;
  for (int address : this->chipsAddresses)
  {
    chipsStr += tr("%1 ").arg(address + 1);
  }
  if (this->chipsAddresses.size() <= 0 || this->chipsAddresses.size() > CHIPS_PER_PLANE * 2)
  {
    qWarning() << Q_FUNC_INFO <<  tr(": Wrong number of chips!");
  }
  this->ui->LineEdit_EnabledChips->setText(chipsStr);
}

void MainWindow::onAgilentDeviceConnectClicked()
{
  QString name = ui->LineEdit_AgilentDeviceName->text();

  this->agilentPort = new QSerialPort(name, this);

  if (this->agilentPort && this->agilentPort->open(QIODevice::ReadWrite))
  {
    this->agilentPort->setBaudRate(QSerialPort::Baud9600);
    this->agilentPort->setDataBits(QSerialPort::Data8);
    this->agilentPort->setParity(QSerialPort::NoParity);
    this->agilentPort->setStopBits(QSerialPort::OneStop);
    this->agilentPort->setFlowControl(QSerialPort::NoFlowControl);

    connect(this->agilentPort, SIGNAL(readyRead()), this, SLOT(agilentSerialPortDataReady()));
    connect(this->agilentPort, SIGNAL(bytesWritten(qint64)), this, SLOT(agilentSerialPortBytesWritten(qint64)));
    connect(this->agilentPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(agilentSerialPortError(QSerialPort::SerialPortError)));

    ui->PushButton_AgilentConnect->setEnabled(false);
    ui->PushButton_AgilentDisconnect->setEnabled(true);
    // freq (Hz)
    std::stringstream freqSstr;
    double freqHz = this->ui->DoubleSpinBox_Frequency->value();
    freqSstr << "FREQ " << std::setprecision(4) << freqHz << '\n';
    std::string freqStringCommand = freqSstr.str();
    // ampl (V)
    std::stringstream amplSstr;
    double mVampl = static_cast<double>(this->ui->HorizontalSlider_Amplitude->value());
    amplSstr << "VOLT " << std::setprecision(4) << (mVampl / 1000.) << '\n';
    std::string amplStringCommand = amplSstr.str();
    // offset (V)
    std::stringstream offSstr;
    double mVoff = static_cast<double>(this->ui->HorizontalSlider_Offset->value());
    offSstr << "VOLT:OFFS " << std::setprecision(4) << (mVoff / 1000.) << '\n';
    std::string offStringCommand = offSstr.str();
    // duty cycle %
    std::stringstream dcycleSstr;
    int dcycle = this->ui->HorizontalSlider_DutyCycle->value();
    dcycleSstr << "PULS:DCYC " << std::setprecision(4) << dcycle << '\n';
    std::string dcycleStringCommand = dcycleSstr.str();

    this->agilentDeviceCommandsList.append(QByteArray("*RST;*CLS\n"));
    this->agilentDeviceCommandsList.append(QByteArray("FUNC:SHAP SQU\n"));
    this->agilentDeviceCommandsList.append(QByteArray( freqStringCommand.c_str(), freqStringCommand.size()));
    this->agilentDeviceCommandsList.append(QByteArray( amplStringCommand.c_str(), amplStringCommand.size()));
    this->agilentDeviceCommandsList.append(QByteArray( offStringCommand.c_str(), offStringCommand.size()));
    this->agilentDeviceCommandsList.append(QByteArray( dcycleStringCommand.c_str(), dcycleStringCommand.size()));
    this->writeNextAgilentCommandFromInitiationList();
  }
  else if (this->agilentPort && !this->agilentPort->isOpen())
  {
    QMessageBox msgBox(this);
    msgBox.setModal(true);
    msgBox.setWindowTitle(tr("IC control"));
    msgBox.setText(tr("Unable to connect device %1.\n%2.").arg(this->agilentPort->portName()).arg(this->agilentPort->errorString()));
    msgBox.exec();
    ui->statusbar->showMessage(QObject::tr("Unable to connect Agilent 33120A"), 1000);

    delete this->agilentPort;
    this->agilentPort = nullptr;
  }
}

void MainWindow::onAgilentDeviceDisconnectClicked()
{
  if (this->agilentPort && this->agilentPort->isOpen())
  {
    this->agilentPort->flush();
    this->agilentPort->close();
    delete this->agilentPort;
    this->agilentPort = nullptr;
  }
  else if (this->agilentPort && !this->agilentPort->isOpen())
  {
    delete this->agilentPort;
    this->agilentPort = nullptr;
  }

  this->agilentDeviceCommandsList.clear();
  ui->PushButton_AgilentConnect->setEnabled(true);
  ui->PushButton_AgilentDisconnect->setEnabled(false);

  ui->statusbar->showMessage(QObject::tr("Agilent 33120A device disconnected"), 1000);
  QApplication::restoreOverrideCursor();
}

void MainWindow::agilentSerialPortBytesWritten(qint64 bytes)
{
  qDebug() << Q_FUNC_INFO << "Serial port data written bytes: " << bytes;
  if (this->agilentDeviceCommandsList.size() && this->lastAgilentCommandWritten.size() == bytes)
  {
    qDebug() << Q_FUNC_INFO << "Agilent command: " << this->lastAgilentCommandWritten;
    this->agilentDeviceCommandsList.pop_front();
    if (this->initiationProgress->isVisible())
    {
      this->initiationProgress->setValue(this->agilentDeviceCommandsList.size());
    }
    QTimer::singleShot( 500, this, SLOT(writeNextAgilentCommandFromInitiationList()));
  }
  if (this->lastAgilentCommandWritten.size() == bytes)
  {
    this->lastAgilentCommandWritten.clear();
    if (this->calibrationEnabled)
    {
      int offset = this->agilentOffsets.front();
      std::vector<int> sideA, sideB;
      this->calibrationChannelsCounts[offset] = std::make_pair( sideA, sideB);
      this->agilentOffsets.pop_front();
      QTimer::singleShot( 100, this, SLOT(onSingleShotClicked()));
    }
  }
}

void MainWindow::agilentSerialPortDataReady()
{
  QByteArray portData = this->agilentPort->readAll();

  qDebug() << Q_FUNC_INFO << "Agilent 33120A data recieved: " << portData.size();
}

void MainWindow::agilentSerialPortError(QSerialPort::SerialPortError)
{
}

void MainWindow::onChipResetClicked()
{
//  unsigned char buf[BUFFER_SIZE] = { 'H' }; // Chip RESET command
  this->lastCommandWritten = ChipResetCommand; //QByteArray( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  if (this->acquisitionPort && this->acquisitionPort->isOpen())
  {
    this->acquisitionPort->write(this->lastCommandWritten);
  }
}

void MainWindow::onAdcResolutionSetClicked()
{
  unsigned char buf[BUFFER_SIZE] = { 'D' };
  buf[1] = this->ui->RadioButton_Adc20Bit->isChecked();

  this->lastCommandWritten = QByteArray( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  if (this->acquisitionPort && this->acquisitionPort->isOpen())
  {
    this->acquisitionPort->write(this->lastCommandWritten);
  }
}

void MainWindow::onSetAmplitudeClicked()
{
  int ampl = this->ui->HorizontalSlider_Amplitude->value(); // mV
  this->setAgilentAmplitude(double(ampl));
}

void MainWindow::setAgilentAmplitude(double ampl_mV)
{
  std::stringstream sstr;
  sstr << "VOLT " << std::setprecision(4) << (ampl_mV / 1000.) << '\n';
  std::string stringCommand = sstr.str();

  this->lastAgilentCommandWritten = QByteArray( stringCommand.c_str(), stringCommand.size());
  if (this->agilentPort && this->agilentPort->isOpen())
  {
    this->agilentPort->write(this->lastAgilentCommandWritten);
  }
}

void MainWindow::onSendCommandClicked()
{
  QString command = this->ui->LineEdit_AgilentCommand->text(); // command
  command += QString(QChar('\n'));
  QString commandUpper = command.toUpper();
  std::string str = commandUpper.toStdString();
  this->lastAgilentCommandWritten = QByteArray(str.c_str(), str.size());
  if (this->agilentPort && this->agilentPort->isOpen())
  {
    this->agilentPort->write(this->lastAgilentCommandWritten);
  }
}

void MainWindow::onSetFrequencyClicked()
{
  double freqHz = this->ui->DoubleSpinBox_Frequency->value(); // Hz
  std::stringstream sstr;
  sstr << "FREQ " << std::setprecision(4) << freqHz << '\n';
  std::string stringCommand = sstr.str();

  this->lastAgilentCommandWritten = QByteArray( stringCommand.c_str(), stringCommand.size());
  if (this->agilentPort && this->agilentPort->isOpen())
  {
    this->agilentPort->write(this->lastAgilentCommandWritten);
  }
}

void MainWindow::onSetDutyCycleClicked()
{
  int dcycPercent = this->ui->SpinBox_DutyCycle->value(); // %
  this->setAgilentDutyCycle(dcycPercent);
}

void MainWindow::onSetOffsetClicked()
{
  int offset = this->ui->HorizontalSlider_Offset->value(); // mV
  this->setAgilentOffset(double(offset));
}

void MainWindow::setAgilentOffset(double offset_mV)
{
  std::stringstream sstr;
  sstr << "VOLT:OFFS " << std::setprecision(4) << (offset_mV / 1000.) << '\n';
  std::string stringCommand = sstr.str();

  this->lastAgilentCommandWritten = QByteArray( stringCommand.c_str(), stringCommand.size());
  if (this->agilentPort && this->agilentPort->isOpen())
  {
    this->agilentPort->write(this->lastAgilentCommandWritten);
  }
}

void MainWindow::setAgilentDutyCycle(int percents)
{
  std::stringstream sstr;
  sstr << "PULS:DCYC " << percents << '\n';
  std::string stringCommand = sstr.str();

  this->lastAgilentCommandWritten = QByteArray( stringCommand.c_str(), stringCommand.size());
  if (this->agilentPort && this->agilentPort->isOpen())
  {
    this->agilentPort->write(this->lastAgilentCommandWritten);
  }
}

void MainWindow::onSetSamplesClicked()
{
//  unsigned char buf[BUFFER_SIZE] = { 'M' };
//  buf[1] = this->ui->HorizontalSlider_Samples->value(); // data

  unsigned char buf[BUFFER_SIZE] = { 'P' };
  int v = this->ui->HorizontalSlider_Samples->value();
  buf[1] = v & 0xFF; // data
  buf[2] = (v >> CHAR_BIT) & 0xFF; // data

  this->lastCommandWritten = QByteArray( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  if (this->acquisitionPort && this->acquisitionPort->isOpen())
  {
    this->acquisitionPort->write(this->lastCommandWritten);
  }
}

void MainWindow::onExternalStartClicked()
{
  unsigned char buf[BUFFER_SIZE] = { 'A' };
  buf[1] = this->ui->CheckBox_ExternalStart->isChecked(); // data
//  qDebug() << Q_FUNC_INFO << "External start: " << (this->ui->CheckBox_ExternalStart->isChecked() ? "Enabled" : "Disabled");

  this->lastCommandWritten = QByteArray( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  if (this->acquisitionPort && this->acquisitionPort->isOpen())
  {
    this->acquisitionPort->write(this->lastCommandWritten);
  }
}

void MainWindow::onSetIntegrationTimeClicked()
{
  unsigned char buf[BUFFER_SIZE] = { 'I' };
  // data is a (intergration time in ms) / 2 minus 1 is a data written into devices
  buf[1] = (this->ui->HorizontalSlider_IntegrationTime->value() / 2) - 1; // data

//  qDebug() << Q_FUNC_INFO << "Integration time code: " << int(buf[1]);

  this->lastCommandWritten = QByteArray( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  if (this->acquisitionPort && this->acquisitionPort->isOpen())
  {
    this->acquisitionPort->write(this->lastCommandWritten);
  }
}

void MainWindow::onSetDevicesEnabled()
{
  unsigned short devsEnabled = this->devicesEnabled();
  unsigned char buf[BUFFER_SIZE] = { 'E' };
  buf[1] = devsEnabled & 0xFF; // enabled low bite
  buf[2] = (devsEnabled >> CHAR_BIT) & 0xFF; // enabled high bite

//  qDebug() << Q_FUNC_INFO << "Enabled devices: " << devsEnabled;

  this->lastCommandWritten = QByteArray( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  if (this->acquisitionPort && this->acquisitionPort->isOpen())
  {
    this->acquisitionPort->write(this->lastCommandWritten);
  }
}

void MainWindow::onSetCapacityClicked()
{
  std::bitset<8> chipIndex(this->ui->HorizontalSlider_CurrentDevice->value() - 1);

  int capacityIndex = this->ui->ComboBox_AcquisitionCapacity->currentIndex();
//  qDebug() << Q_FUNC_INFO << "Capacity index: " << capacityIndex;
  std::bitset<3> capacity(capacityIndex);
  chipIndex.set(5, capacity.test(0));
  chipIndex.set(6, capacity.test(1));
  chipIndex.set(7, capacity.test(2));

  unsigned char buf[BUFFER_SIZE] = { 'C' };
  buf[1] = static_cast<unsigned char>(chipIndex.to_ulong()); // data

  this->lastCommandWritten = QByteArray( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  if (this->acquisitionPort && this->acquisitionPort->isOpen())
  {
    this->acquisitionPort->write(this->lastCommandWritten);
  }
}

void MainWindow::onSetNumberOfChipsClicked()
{
//  this->ui->HorizontalSlider_Chip->setMaximum(this->ui->SpinBox_Devices->value());
//  this->ui->SpinBox_Chip->setMaximum(this->ui->SpinBox_Devices->value());

  unsigned char buf[BUFFER_SIZE] = { 'O' };
  buf[1] = this->ui->HorizontalSlider_Devices->value(); // data

  this->lastCommandWritten = QByteArray( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  if (this->acquisitionPort && this->acquisitionPort->isOpen())
  {
    this->acquisitionPort->write(this->lastCommandWritten);
  }
}

void MainWindow::onWriteCapacitiesClicked()
{
//  unsigned char buf[BUFFER_SIZE] = { 'G', 0 };

  this->lastCommandWritten = WriteCapacitiesCommand; //QByteArray( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  if (this->acquisitionPort && this->acquisitionPort->isOpen())
  {
    this->acquisitionPort->write(this->lastCommandWritten);
  }
}

void MainWindow::onAlteraResetClicked()
{
//  unsigned char buf[BUFFER_SIZE] = { 'R', 0 }; // Altera reset command

  this->lastCommandWritten = AlteraResetCommand; //QByteArray( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  if (this->acquisitionPort && this->acquisitionPort->isOpen())
  {
    this->acquisitionPort->write(this->lastCommandWritten);
  }
}

void MainWindow::onAcquisitionClicked()
{
//  unsigned char buf[BUFFER_SIZE] = { 'B', 0 }; // Acquisition command

  this->acquisitionDataBuffer.clear();
  this->channelsCountsA.clear();
  this->channelsCountsB.clear();
  this->chipsAddresses.clear();

  this->lastCommandWritten = AcquisitionCommand; //QByteArray( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  if (this->acquisitionPort && this->acquisitionPort->isOpen())
  {
    this->acquisitionPort->write(this->lastCommandWritten);
  }
}

void MainWindow::onSingleShotClicked()
{
//  unsigned char buf[BUFFER_SIZE] = { 'S', 0 }; // Single shot command

  this->lastCommandWritten = SingleShotCommand; //QByteArray( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  if (this->acquisitionPort && this->acquisitionPort->isOpen())
  {
    this->acquisitionPort->write(this->lastCommandWritten);
  }
}

void MainWindow::onAcquisitionAdcModeResolutionChanged(QAbstractButton* button)
{
  QRadioButton* radioButton = qobject_cast<QRadioButton*>(button);
  if (!radioButton)
  {
    return;
  }

//  QApplication::setOverrideCursor(Qt::WaitCursor);
  if (radioButton == this->ui->RadioButton_Adc16Bit)
  {
//    this->getHorizontalStripsHist()->SetBins(CHANNELS_PER_PLANE, .5, double(CHANNELS_PER_PLANE) - .5, Resolution16Bit / 4, -1000., double(Resolution16Bit) - 1001.);
//    this->getVerticalStripsHist()->SetBins(CHANNELS_PER_PLANE, .5, double(CHANNELS_PER_PLANE) - .5, Resolution16Bit / 4, -1000., double(Resolution16Bit) - 1001.);
    this->getChannelHistSideA()->SetBins(RESOLUTION_16BIT / 4, -1000., double(RESOLUTION_16BIT) - 1001.);
    this->getChannelHistSideB()->SetBins(RESOLUTION_16BIT / 4, -1000., double(RESOLUTION_16BIT) - 1001.);
  }
  else if (radioButton == this->ui->RadioButton_Adc20Bit)
  {
//    this->getHorizontalStripsHist()->SetBins(CHANNELS_PER_PLANE, .5, double(CHANNELS_PER_PLANE) - .5, Resolution20Bit / 4, -1000., double(Resolution20Bit) - 1001.);
//    this->getVerticalStripsHist()->SetBins(CHANNELS_PER_PLANE, .5, double(CHANNELS_PER_PLANE) - .5, Resolution20Bit / 4, -1000., double(Resolution20Bit) - 1001.);
    this->getChannelHistSideA()->SetBins(RESOLUTION_20BIT / 16, -1000., (double(RESOLUTION_20BIT) / 4) - 1001.);
    this->getChannelHistSideB()->SetBins(RESOLUTION_20BIT / 16, -1000., (double(RESOLUTION_20BIT) / 4) - 1001.);
  }
//  this->hist2Pad[ORIENTATION_HORIZONTAL]->Modified();
//  this->hist2Pad[ORIENTATION_HORIZONTAL]->Update();
//  this->hist2Pad[ORIENTATION_VERTICAL]->Modified();
//  this->hist2Pad[ORIENTATION_VERTICAL]->Update();
  this->channelHistPad[SIDE_A]->Modified();
  this->channelHistPad[SIDE_A]->Update();
  this->channelHistPad[SIDE_B]->Modified();
  this->channelHistPad[SIDE_B]->Update();
  QApplication::restoreOverrideCursor();
}

void MainWindow::onCameraNumberChanged(QAbstractButton* button)
{
  QRadioButton* radioButton = qobject_cast<QRadioButton*>(button);
  if (!radioButton)
  {
    return;
  }

  if (radioButton == this->ui->RadioButton_Camera1)
  {
    this->ui->LineEdit_AcquisitionDeviceName->setText("/dev/ft2232h_ic01_b");
    this->ui->LineEdit_DataDeviceName->setText("/dev/ft2232h_ic01_a");
    /// Camera1
//    ChipsVerticalStrips = { 7, 3, 5, 6, 1, 8  };
//    ChipsHorizontalStrips = { 10, 11, 12, 4, 2, 9 };
  }
  else if (radioButton == this->ui->RadioButton_Camera2)
  {
    /// Camera2
    ChipsVerticalStrips = { 11, 2, 12, 1 };
    ChipsHorizontalStrips = { 6, 3, 5, 9, 4, 10 };
    this->ui->LineEdit_AcquisitionDeviceName->setText("/dev/ft2232h_ic02_b");
    this->ui->LineEdit_DataDeviceName->setText("/dev/ft2232h_ic02_a");
  }
}

int MainWindow::currentCameraNumber() const
{
  QAbstractButton* button = this->ui->ButtonGroup_SelectedCamera->checkedButton();
  QRadioButton* radioButton = qobject_cast< QRadioButton* >(button);

  if (!radioButton)
  {
    return -1;
  }

  if (radioButton == this->ui->RadioButton_Camera1)
  {
    return 1;
  }
  else if (radioButton == this->ui->RadioButton_Camera2)
  {
    return 2;
  }
  return -1;
}

void MainWindow::storeSpillData(const QDateTime& timeStamp)
{
  if (!rootFile)
  {
    return;
  }

  QString spillPrefix = this->ui->LineEdit_SpillPrefix->text();
  QString spillDataString = QObject::tr("%1_%2").arg(spillNumber++).arg(timeStamp.toString("ddMMyyyy_hhmmss"));
  if (!spillPrefix.isEmpty())
  {
    spillDataString = spillPrefix + QString(QChar('_')) + spillDataString;
  }

  std::string spillStdString = spillDataString.toStdString();
  std::string titleStdString = "IC events at date and time " + spillStdString;
  std::unique_ptr<TTree> spillTree(new TTree(spillStdString.c_str(), titleStdString.c_str()));
  this->ui->Label_LastSpillName->setText(spillDataString);

  int capacityCode = this->ui->ComboBox_AcquisitionCapacity->currentIndex();
  int integrationTimeCode = (this->ui->HorizontalSlider_IntegrationTime->value() / 2) - 1;

  unsigned int mode = (capacityCode << 4) | integrationTimeCode;

  std::vector< char > buffer(this->acquisitionDataBuffer.size(), 0);
  std::copy(this->acquisitionDataBuffer.begin(), this->acquisitionDataBuffer.end(), buffer.begin());

  std::vector< char >::size_type bufferSize = buffer.size();

  int dataBits = -1;
  if (ui->RadioButton_Adc16Bit->isChecked())
  {
    dataBits = AdcResolutionType::ADC_16_BIT;;
  }
  else if (ui->RadioButton_Adc20Bit->isChecked())
  {
    dataBits = AdcResolutionType::ADC_20_BIT;;
  }

  spillTree->Branch("respChipsEnabled", &chamberResponse.ChipsEnabled, "respChipsEnabled/I");
  spillTree->Branch("respChipsEnabledCode", &chamberResponse.ChipsEnabledCode, "respChipsEnabledCode/s");
  spillTree->Branch("respIntTime", &chamberResponse.IntegrationTimeCode, "respIntTime/I");
  spillTree->Branch("respCapacity", &chamberResponse.CapacityCode, "respCapacity/I");
  spillTree->Branch("respExtStart", &chamberResponse.ExternalStartState, "respExtStart/O");
  spillTree->Branch("respAdcMode", &chamberResponse.AdcMode, "respAdcMode/I");

  spillTree->Branch("mode", &mode, "mode/i");
  spillTree->Branch("bufferSize", &bufferSize, "bufferSize/l");
  spillTree->Branch("adcMode", &dataBits, "adcMode/I");

  const std::vector< char >* bufferPtr = &buffer;
  spillTree->Branch("bufferVector", "std::vector< char >", &bufferPtr);

  std::vector< int >::size_type chipsAcquired = this->chipsAddresses.size();
  std::vector< int >* chipsAcquiredPtr = &this->chipsAddresses;
  spillTree->Branch("chipsAcquired", &chipsAcquired, "chipsAcquired/l");
  spillTree->Branch("chipsAcquiredVector", "std::vector< int >", &chipsAcquiredPtr);

  spillTree->Fill();
  spillTree->Write();
}

void MainWindow::storeCalibrationData(int offset, const std::vector<int>& sideA, const std::vector<int>& sideB)
{
  QString calibPrefix = this->ui->LineEdit_CalibrationLabel->text();
  if (calibPrefix.isEmpty())
  {
    calibPrefix = "None";
  }

  std::stringstream ss;
  ss << "calib_" << offset;
  std::string titleStdString = ss.str();
  std::string descrStdString = std::string("Calibration_") + calibPrefix.toStdString();
  std::unique_ptr<TTree> calibrationTree(new TTree(titleStdString.c_str(), descrStdString.c_str()));
  calibrationTree->Branch("offset", &offset, "offset/I");

  std::vector<int>::size_type sizeA = sideA.size();
  std::vector<int>::size_type sizeB = sideB.size();

  calibrationTree->Branch("sizeA", &sizeA, "sizeA/l");
  calibrationTree->Branch("sizeB", &sizeB, "sizeB/l");
  const std::vector<int>* sideAPtr = &sideA;
  const std::vector<int>* sideBPtr = &sideB;
  calibrationTree->Branch("sideA", "std::vector<int>", &sideAPtr);
  calibrationTree->Branch("sideB", "std::vector<int>", &sideBPtr);
  calibrationTree->Fill();
  calibrationTree->Write();
}

void MainWindow::storeTangentData(int calcBegin, int calcEnd, double tanSideA[CHANNELS_PER_CHIP], double tanSideB[CHANNELS_PER_CHIP])
{
  QString calibPrefix = this->ui->LineEdit_CalibrationLabel->text();
  if (calibPrefix.isEmpty())
  {
    calibPrefix = "None";
  }
  std::string titleStdString = std::string("tangent_") + calibPrefix.toStdString();
  std::unique_ptr<TTree> tangentTree(new TTree(titleStdString.c_str(), "tangent"));
  Int_t channelsPerChip = CHANNELS_PER_CHIP;
  tangentTree->Branch("calcBegin", &calcBegin, "calcBegin/I");
  tangentTree->Branch("calcEnd", &calcEnd, "calcEnd/I");
  tangentTree->Branch("channelsPerChip", &channelsPerChip, "channelsPerChip/I");
  tangentTree->Branch("tanSideA", tanSideA, "tanSideA[channelsPerChip]/D");
  tangentTree->Branch("tanSideB", tanSideB, "tanSideB[channelsPerChip]/D");
  tangentTree->Fill();
  tangentTree->Write();
}

void MainWindow::onProcessSpillChannelsCountsClicked()
{
  this->getHorizontalStripsGraph()->Clear();
  this->getVerticalStripsGraph()->Clear();
  this->getHorizontalCalibratedStripsGraph()->Clear();
  this->getVerticalCalibratedStripsGraph()->Clear();

  for (int chipStrip = 0; chipStrip < CHANNELS_PER_PLANE; ++chipStrip)
  {
    this->getHorizontalStripsGraph()->SetPoint( chipStrip, Double_t(chipStrip), 0.);
    this->getHorizontalStripsGraph()->SetPointError( chipStrip, 0., 0.);
    this->getHorizontalCalibratedStripsGraph()->SetPoint( chipStrip, Double_t(chipStrip), 0.);
    this->getHorizontalCalibratedStripsGraph()->SetPointError( chipStrip, 0., 0.);
  }
  for (int chipStrip = 0; chipStrip < CHANNELS_PER_CHIP * 4; ++chipStrip)
  {
    this->getVerticalStripsGraph()->SetPoint( chipStrip, Double_t(chipStrip), 0.);
    this->getVerticalStripsGraph()->SetPointError( chipStrip, 0., 0.);
    this->getVerticalCalibratedStripsGraph()->SetPoint( chipStrip, Double_t(chipStrip), 0.);
    this->getVerticalCalibratedStripsGraph()->SetPointError( chipStrip, 0., 0.);
  }
  std::bitset< CHIPS_PER_PLANE * 2 > devices(chamberResponse.ChipsEnabledCode);

  const int xBins = CHANNELS_PER_CHIP * 4;
//  this->hist2D->Reset();
  if (this->ui->CheckBox_RawData->isChecked())
  {
    const Double_t* xBinsBorders = VerticalStripsBinsRaw.data();
    this->hist2D->SetBins(xBins, xBinsBorders);
  }
  else
  {
    const Double_t* xBinsBorders = VerticalStripsBinsCorrect.data();
    this->hist2D->SetBins(xBins, xBinsBorders);
  }

  int nofChips = static_cast< int >(devices.count());
  this->ui->TableWidget_ChannelPedSignalInfo->setRowCount(nofChips * CHANNELS_PER_CHIP);
  qDebug() << Q_FUNC_INFO << "Number of chips: " << nofChips;

  int intTimeMs = this->ui->HorizontalSlider_IntegrationTime->value() / 2;
  qDebug() << Q_FUNC_INFO << "Integration time index: " << intTimeMs;
  int pedBegin = static_cast<int>(this->ui->SpinBox_PedBegin->value() / (2 * intTimeMs));
  int pedEnd = static_cast<int>(this->ui->SpinBox_PedEnd->value() / (2 * intTimeMs));
  int sigBegin = static_cast<int>(this->ui->SpinBox_SignalBegin->value() / (2 * intTimeMs));
  int sigEnd = static_cast<int>(this->ui->SpinBox_SignalEnd->value() / (2 * intTimeMs));

  if (this->ui->CheckBox_RawData->isChecked())
  {
    pedBegin = static_cast<int>(this->ui->SpinBox_PedBegin->value() / intTimeMs);
    pedEnd = static_cast<int>(this->ui->SpinBox_PedEnd->value() / intTimeMs);
    sigBegin = static_cast<int>(this->ui->SpinBox_SignalBegin->value() / intTimeMs);
    sigEnd = static_cast<int>(this->ui->SpinBox_SignalEnd->value() / intTimeMs);
  }
  if (pedBegin > pedEnd)
  {
    std::swap< int >( pedBegin, pedEnd);
  }
  if (sigBegin > sigEnd)
  {
    std::swap< int >( sigBegin, sigEnd);
  }
  qDebug() << Q_FUNC_INFO << pedBegin << ' ' << pedEnd << ' ' << sigBegin << ' ' << sigEnd;

  std::array< std::pair< int, int >, CHANNELS_PER_PLANE > HorizontalChipChannels; // for mixed channels between opposite chips
  std::array< std::pair< int, int >, CHANNELS_PER_CHIP * 4 > VerticalChipChannels; // for mixed channels between opposite chips

  auto formChipStrip = [](const std::array< std::pair< int, int >, CHANNELS_PER_PLANE >& chipStripMask,
    std::array< std::pair< int, int >, CHANNELS_PER_PLANE >& formStripMask) {
    const size_t half = chipStripMask.size() / 2;
    for (size_t i = 0, j = 0; j < chipStripMask.size(); )
    {
      formStripMask[j++] = chipStripMask[half + i];
      formStripMask[j++] = chipStripMask[i];
      i++;
    }
  };
  auto formChipStrip1 = [](const std::array< std::pair< int, int >, CHANNELS_PER_CHIP * 4 >& chipStripMask,
    std::array< std::pair< int, int >, CHANNELS_PER_CHIP * 4 >& formStripMask) {
    std::array< std::pair< int, int >, CHANNELS_PER_CHIP > chip12;
    std::copy(chipStripMask.begin(), chipStripMask.end(), formStripMask.begin());

    // save chip12
    for (size_t i = CHANNELS_PER_CHIP * 2, j = 0; i < CHANNELS_PER_CHIP * 3; ++i)
    {
      chip12[j++] = chipStripMask[i];
    }
    // mix chip1, chip2
    for (size_t i = 0, j = 0; i < CHANNELS_PER_CHIP; i++)
    {
      std::pair< int, int > chip2 = chipStripMask[CHANNELS_PER_CHIP + i];
      std::pair< int, int > chip1 = chipStripMask[CHANNELS_PER_CHIP * 3 + i];
      formStripMask[CHANNELS_PER_CHIP + j++] = chip1;
      formStripMask[CHANNELS_PER_CHIP + j++] = chip2;
    }
    // copy chip12 to the end
    for (size_t i = CHANNELS_PER_CHIP * 3, j = 0; i < chipStripMask.size(); ++i, ++j)
    {
      formStripMask[i] = chip12[j];
    }
  };
  // Fill mixed channels array of strip positions between opposite chips

//  formChipStrip( HorizontalChipChannelStrips, HorizontalChipChannels); // horizontal
//  formChipStrip( VerticalChipChannelStrips, VerticalChipChannels); // vertical

  formChipStrip( this->horizontalChipChannelStrips, HorizontalChipChannels); // horizontal
  formChipStrip1( this->verticalChipChannelStrips, VerticalChipChannels); // vertical

  if (this->chipsAddresses.size() != static_cast< size_t >(nofChips))
  {
    qWarning() << Q_FUNC_INFO << tr("Wrong number of chips for reconsruction.\nChips enabled: %1, chips acquired: %2").arg(nofChips).arg(this->chipsAddresses.size());
//    QMessageBox msgBox(this);
//    msgBox.setIcon(QMessageBox::Critical);
//    msgBox.setModal(true);
//    msgBox.setWindowTitle(tr("IC control"));
//    msgBox.setText(tr("Wrong number of chips for reconsruction.\nChips enabled: %1, chips acquired: %2").arg(nofChips).arg(this->chipsAddresses.size()));
//    msgBox.exec();
  }
  std::pair< int, int > ref( 1, 1); // reference chip == 1, strip == 1
  std::pair< int, int > refAmplitude( 1, 1); // amplitude reference chip == 2, strip == 15
  double refA = this->chipChannelCalibrationA[ref]; // reference value side-A
  double refB = this->chipChannelCalibrationB[ref]; // reference value side-B
  double refAmpl = this->chipChannelCalibrationAmplitude[refAmplitude]; // reference amplitude value

  int capIndex = this->ui->ComboBox_AcquisitionCapacity->currentIndex();
  double cap = CapacityCoefficient[capIndex];
  int intTime = this->ui->HorizontalSlider_IntegrationTime->value();
  QString text = this->ui->LineEdit_SpillPrefix->text();

  std::stringstream filenameStream;
  filenameStream << "ChannelsAmp_" << text.toStdString() << '_' << cap << '_' << intTime << ".txt";
  std::string filename = filenameStream.str();
  std::ofstream data(filename);

  int k = 0;
  for (auto iter = this->chipsAddresses.begin(); iter != this->chipsAddresses.end(); ++iter)
  {
    int chipAddress = *iter;
    auto tmp = devices;
    ReverseBits< CHIPS_PER_PLANE * 2 >(tmp);
    if ((chipAddress < 0) || (chipAddress > CHIPS_PER_PLANE * 2) || !tmp.test(chipAddress))
    {
      // Skip data for wrong chip address
      continue;
    }
    for (int i = 0; i < CHANNELS_PER_CHIP; ++i)
    {
      std::pair< int, int > curr( chipAddress + 1, i + 1); // current chip, strip
      double currA = this->chipChannelCalibrationA[curr]; // current value side-A
      double currB = this->chipChannelCalibrationB[curr]; // current value side-B
      double currAmpl = this->chipChannelCalibrationAmplitude[curr]; // current amplitude value
      std::vector<int>& sideA = this->channelsCountsA[chipAddress][i];
      std::vector<int>& sideB = this->channelsCountsB[chipAddress][i];
      MeanDispAccumType statPedB, statCalibPedB;
      MeanDispAccumType statSigB, statCalibSigB;
      MeanDispAccumType statPedA, statCalibPedA;
      MeanDispAccumType statSigA, statCalibSigA;

      for (int j = pedBegin; j < pedEnd; ++j)
      {
        statCalibPedA(double(sideA[j]) * refA / currA);
        statCalibPedB(double(sideB[j]) * refB / currB);
        statPedA(sideA[j]);
        statPedB(sideB[j]);
      }
      for (int j = sigBegin; j < sigEnd; ++j)
      {
        statCalibSigA(double(sideA[j]) * refA / currA);
        statCalibSigB(double(sideB[j]) * refB / currB);
        statSigA(sideA[j]);
        statSigB(sideB[j]);
      }
      ChannelInfo info, infoCalib;
      info.pedMeanA = boost::accumulators::mean(statPedA);
      info.pedMeanB = boost::accumulators::mean(statPedB);
      info.pedMom2A = boost::accumulators::moment< 2 >(statPedA);
      info.pedMom2B = boost::accumulators::moment< 2 >(statPedB);
      info.sigMeanA = boost::accumulators::mean(statSigA);
      info.sigMeanB = boost::accumulators::mean(statSigB);
      info.sigMom2A = boost::accumulators::moment< 2 >(statSigA);
      info.sigMom2B = boost::accumulators::moment< 2 >(statSigB);
      info.sigCountA = boost::accumulators::count(statSigA);
      info.sigCountB = boost::accumulators::count(statSigB);
      info.sigSumA = boost::accumulators::sum(statSigA);
      info.sigSumB = boost::accumulators::sum(statSigB);

      infoCalib.pedMeanA = boost::accumulators::mean(statCalibPedA);
      infoCalib.pedMeanB = boost::accumulators::mean(statCalibPedB);
      infoCalib.sigMeanA = boost::accumulators::mean(statCalibSigA);
      infoCalib.sigMeanB = boost::accumulators::mean(statCalibSigB);
      infoCalib.sigCountA = boost::accumulators::count(statCalibSigA);
      infoCalib.sigCountB = boost::accumulators::count(statCalibSigB);
      infoCalib.sigSumA = boost::accumulators::sum(statCalibSigA);
      infoCalib.sigSumB = boost::accumulators::sum(statCalibSigB);
      infoCalib.sigMom2A = boost::accumulators::moment< 2 >(statCalibSigA);
      infoCalib.sigMom2B = boost::accumulators::moment< 2 >(statCalibSigB);

      double signalA = (info.sigSumA - info.sigCountA * info.pedMeanA) / info.sigCountA;
      double signalB = (info.sigSumB - info.sigCountB * info.pedMeanB) / info.sigCountB;
      double channelSignal = (signalA + signalB) / 2.;

      double calibSignalA = (infoCalib.sigSumA - infoCalib.sigCountA * infoCalib.pedMeanA) / infoCalib.sigCountA;
      double calibSignalB = (infoCalib.sigSumB - infoCalib.sigCountB * infoCalib.pedMeanB) / infoCalib.sigCountB;
      double calibChannelSignal = refAmpl * (calibSignalA + calibSignalB) / (2. * currAmpl);
      double calibDispSigA = infoCalib.sigMom2A - infoCalib.sigMeanA * infoCalib.sigMeanA;

      double dispPedA = info.pedMom2A - info.pedMeanA * info.pedMeanA;
      double dispPedB = info.pedMom2B - info.pedMeanB * info.pedMeanB;
      double dispSigA = info.sigMom2A - info.sigMeanA * info.sigMeanA;
      double dispSigB = info.sigMom2B - info.sigMeanB * info.sigMeanB;

      QTableWidgetItem* item = new QTableWidgetItem(tr("%1").arg(chipAddress + 1));
      int chipStrip = chipAddress * CHANNELS_PER_CHIP + i;
      int chipStripPos = k * CHANNELS_PER_CHIP + i;
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 0, item);
      item = new QTableWidgetItem(tr("%1").arg(i + 1));
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 1, item);
      item = new QTableWidgetItem(tr("%1").arg(info.pedMeanA));
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 2, item);
      item = new QTableWidgetItem(tr("%1").arg(std::sqrt(dispPedA)));
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 3, item);
      item = new QTableWidgetItem(tr("%1").arg(info.pedMeanB));
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 4, item);
      item = new QTableWidgetItem(tr("%1").arg(std::sqrt(dispPedB)));
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 5, item);
      item = new QTableWidgetItem(tr("%1").arg(info.sigMeanA - info.pedMeanA));
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 6, item);
      item = new QTableWidgetItem(tr("%1").arg(std::sqrt(dispSigA)));
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 7, item);
      item = new QTableWidgetItem(tr("%1").arg(info.sigMeanB - info.pedMeanB));
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 8, item);
      item = new QTableWidgetItem(tr("%1").arg(std::sqrt(dispSigB)));
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 9, item);
      item = new QTableWidgetItem(tr("%1").arg(signalA));
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 10, item);
      item = new QTableWidgetItem(tr("%1").arg(signalB));
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 11, item);
      item = new QTableWidgetItem(tr("%1").arg(channelSignal));
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 12, item);
      item = new QTableWidgetItem(tr("%1").arg((info.sigMeanA - info.pedMeanA) / std::sqrt(dispPedA)));
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 13, item);
      item = new QTableWidgetItem(tr("%1").arg((info.sigMeanB - info.pedMeanB) / std::sqrt(dispPedB)));
      this->ui->TableWidget_ChannelPedSignalInfo->setItem( chipStripPos, 14, item);

      data << chipAddress + 1 << ' ' << i + 1 << ' ' << info.pedMeanA << ' ' << std::sqrt(dispPedA) \
           << ' ' << info.pedMeanB << ' ' << std::sqrt(dispPedB) << ' ' << info.sigMeanA - info.pedMeanA \
           << ' ' << std::sqrt(dispSigA) << ' ' << info.sigMeanB - info.pedMeanB << ' ' << std::sqrt(dispSigB) \
           << ' ' << signalA << ' ' << signalB << ' ' << channelSignal << ' ' \
           << (info.sigMeanA - info.pedMeanA) / std::sqrt(dispPedA) << ' ' \
           << (info.sigMeanB - info.pedMeanB) / std::sqrt(dispPedB) << '\n';

      double MeanSignalCountToCharge = CapacityChargeCoefficient[ui->ComboBox_AcquisitionCapacity->currentIndex()];
      if (ui->RadioButton_Adc16Bit->isChecked())
      {
        MeanSignalCountToCharge /= double(RESOLUTION_16BIT);
      }
      else if (ui->RadioButton_Adc20Bit->isChecked())
      {
        MeanSignalCountToCharge /= double(RESOLUTION_20BIT);
      }
      else
      {
        MeanSignalCountToCharge /= double(RESOLUTION_16BIT);
      }

      std::pair< int, int > chipChannel( chipAddress + 1, i + 1);

      auto findChipStrip = [chipChannel](const std::array< std::pair< int, int >, CHANNELS_PER_PLANE >& chipStripMask) -> int {
        auto iterPos = std::find(chipStripMask.begin(), chipStripMask.end(), chipChannel);
        if (iterPos != chipStripMask.end())
        {
          return static_cast< int >(iterPos - chipStripMask.begin());
        }
        return -1;
      };

      auto findChipStrip1 = [chipChannel](const std::array< std::pair< int, int >, CHANNELS_PER_CHIP * 4 >& chipStripMask) -> int {
        auto iterPos = std::find(chipStripMask.begin(), chipStripMask.end(), chipChannel);
        if (iterPos != chipStripMask.end())
        {
          return static_cast< int >(iterPos - chipStripMask.begin());
        }
        return -1;
      };

      constexpr double channelStepErrorPerSideMM = 1. / std::sqrt(12.);

      if (std::find(std::begin(ChipsHorizontalStrips), std::end(ChipsHorizontalStrips), chipAddress + 1) != ChipsHorizontalStrips.end())
      { // Horizontal strips (Vertical profile)
        if (!this->ui->CheckBox_RawData->isChecked())
        {
          chipStrip = findChipStrip(HorizontalChipChannels);
        }
        else
        {
          chipStrip = findChipStrip(this->horizontalChipChannelStrips);
        }
        this->getHorizontalStripsHist()->Fill( chipStrip + 1, calibChannelSignal);
        this->getHorizontalStripsGraph()->SetPoint( chipStrip, Double_t(chipStrip), channelSignal);
        this->getHorizontalStripsGraph()->SetPointError( chipStrip, 0., std::sqrt(dispSigA));
        this->getHorizontalCalibratedStripsGraph()->SetPoint( chipStrip, Double_t(chipStrip), calibChannelSignal);
        this->getHorizontalCalibratedStripsGraph()->SetPointError( chipStrip, 0., std::sqrt(calibDispSigA));
        if ((this->ui->CheckBox_RawData->isChecked() && chipStrip == 36) || (!this->ui->CheckBox_RawData->isChecked() && chipStrip == 73))
        {
          this->getHorizontalCalibratedStripsGraph()->SetPoint( chipStrip, Double_t(chipStrip), 0.0);
          this->getHorizontalCalibratedStripsGraph()->SetPointError( chipStrip, 0., 0.);
        }
        Double_t x = Double_t(chipStrip) * (this->channelStepPerSideMM / 2.); // coordinate X of the strip
        Double_t x_err = (this->channelStepPerSideMM / 2.) * channelStepErrorPerSideMM;
        if (this->ui->CheckBox_RawData->isChecked())
        {
          x *= 2.;
          x_err *= 2.;
        }
        this->graphFit[ORIENTATION_HORIZONTAL]->SetPoint(chipStrip, x, calibChannelSignal * MeanSignalCountToCharge);
//        this->graphFit[ORIENTATION_HORIZONTAL]->SetPoint(chipStrip, x, (infoCalib.sigMeanA - infoCalib.pedMeanA) * MeanSignalCountToCharge);
        this->graphFit[ORIENTATION_HORIZONTAL]->SetPointError(chipStrip, x_err, std::sqrt(calibDispSigA) * MeanSignalCountToCharge);
      }
      else if (std::find(std::begin(ChipsVerticalStrips), std::end(ChipsVerticalStrips), chipAddress + 1) != ChipsVerticalStrips.end())
      { // Vertical strips (Horizontal profile)
        if (!this->ui->CheckBox_RawData->isChecked())
        {
          chipStrip = findChipStrip1(VerticalChipChannels);
        }
        else
        {
          chipStrip = findChipStrip1(this->verticalChipChannelStrips);
        }
        this->getVerticalStripsHist()->Fill( chipStrip + 1, calibChannelSignal);
        this->getVerticalStripsGraph()->SetPoint( chipStrip, Double_t(chipStrip), channelSignal);
        this->getVerticalStripsGraph()->SetPointError( chipStrip, 0., std::sqrt(dispSigA));
        this->getVerticalCalibratedStripsGraph()->SetPoint( chipStrip, Double_t(chipStrip), calibChannelSignal);
        this->getVerticalCalibratedStripsGraph()->SetPointError( chipStrip, 0., std::sqrt(calibDispSigA));
        Double_t x = Double_t(chipStrip) * (this->channelStepPerSideMM / 2.); // coordinate Y of the strip
        Double_t x_err = (this->channelStepPerSideMM / 2.) * channelStepErrorPerSideMM;
        if (this->ui->CheckBox_RawData->isChecked())
        {
          x *= 2.;
          x_err *= 2.;
        }
//        this->graphFit[ORIENTATION_VERTICAL]->SetPoint(chipStrip, x, (infoCalib.sigMeanA - infoCalib.pedMeanA) * MeanSignalCountToCharge);
        this->graphFit[ORIENTATION_VERTICAL]->SetPoint(chipStrip, x, calibChannelSignal * MeanSignalCountToCharge);
        this->graphFit[ORIENTATION_VERTICAL]->SetPointError(chipStrip, x_err, std::sqrt(calibDispSigA) * MeanSignalCountToCharge);
      }
    }
    k++;
  }
  data.close();

  for (Int_t horizStrips = 0; horizStrips < CHANNELS_PER_PLANE; ++horizStrips)
  {
    for (Int_t vertStrips = 0; vertStrips < CHANNELS_PER_CHIP * 4; ++vertStrips)
    {
      Double_t xV, yV, xH, yH;
      Int_t pos = this->getVerticalCalibratedStripsGraph()->GetPoint( vertStrips, xV, yV);
      pos = this->getHorizontalCalibratedStripsGraph()->GetPoint( horizStrips, xH, yH);
      this->hist2D->SetBinContent( vertStrips, horizStrips, yH * yV);
      Q_UNUSED(pos);
    }
  }

  this->hist2Pad[ORIENTATION_VERTICAL]->Modified();
  this->hist2Pad[ORIENTATION_VERTICAL]->Update();
  this->graphPad[ORIENTATION_VERTICAL]->Modified();
  this->graphPad[ORIENTATION_VERTICAL]->Update();
  this->hist2Pad[ORIENTATION_HORIZONTAL]->Modified();
  this->hist2Pad[ORIENTATION_HORIZONTAL]->Update();
  this->graphPad[ORIENTATION_HORIZONTAL]->Modified();
  this->graphPad[ORIENTATION_HORIZONTAL]->Update();
  this->padFit[ORIENTATION_VERTICAL]->Modified();
  this->padFit[ORIENTATION_VERTICAL]->Update();
  this->padFit[ORIENTATION_HORIZONTAL]->Modified();
  this->padFit[ORIENTATION_HORIZONTAL]->Update();
  this->pseudo2DPad->Modified();
  this->pseudo2DPad->Update();
}

void MainWindow::saveSettings()
{
  QSettings set;
  int cameraNumber = this->currentCameraNumber();
  QString acquisitionDeviceName = ui->LineEdit_AcquisitionDeviceName->text();
  QString dataDeviceName = ui->LineEdit_DataDeviceName->text();
  switch (cameraNumber)
  {
  case 1:
  case 2:
    set.setValue( "camera-number", cameraNumber);
    set.setValue( "device-name", acquisitionDeviceName);
    set.setValue( "data-device-name", dataDeviceName);
    break;
  default:
    break;
  }

  int run = ui->SpinBox_RunNumber->value();
  set.setValue( "run-number", run);

  int devices = ui->HorizontalSlider_Devices->value();
  set.setValue( "nof-chips", devices);
  int capacityIndex = ui->ComboBox_AcquisitionCapacity->currentIndex();
  set.setValue( "capacity-index", capacityIndex);
  if (ui->RadioButton_Adc16Bit->isChecked())
  {
    set.setValue( "adc-resolution", int(16));
  }
  else
  {
    set.setValue( "adc-resolution", int(20));
  }
  int intTime = ui->HorizontalSlider_IntegrationTime->value();
  set.setValue( "integration-time", intTime);

  int samples = ui->HorizontalSlider_Samples->value();
  set.setValue( "acquisition-samples", samples);

  int pedBegin = ui->SpinBox_PedBegin->value();
  set.setValue( "ped-begin", pedBegin);
  int pedEnd = ui->SpinBox_PedEnd->value();
  set.setValue( "ped-end", pedEnd);
  int signalBegin = ui->SpinBox_SignalBegin->value();
  set.setValue( "signal-begin", signalBegin);
  int signalEnd = ui->SpinBox_SignalEnd->value();
  set.setValue( "signal-end", signalEnd);
  QString spillPrefix = ui->LineEdit_SpillPrefix->text();
  set.setValue( "spill-prefix", spillPrefix);

  set.beginWriteArray("chips");
  for (size_t i = 0; i < this->CheckBox_DevicesEnabled.size(); ++i)
  {
    set.setArrayIndex(i);
    set.setValue("checked", this->CheckBox_DevicesEnabled[i]->isChecked());
  }
  set.endArray();
}

void MainWindow::loadSettings()
{
  QSettings set;

  int run = set.value( "run-number", 0).toInt();
  ui->SpinBox_RunNumber->setValue(run);

  QString name = set.value( "device-name", "/dev/ft2232h_ic_b").toString();
  ui->LineEdit_AcquisitionDeviceName->setText(name);
  QString dataName = set.value( "data-device-name", "/dev/ft2232h_ic_a").toString();
  ui->LineEdit_DataDeviceName->setText(dataName);
/*
  int cameraNumber = set.value( "camera-number", 1).toInt();
  switch (cameraNumber)
  {
  case 1:
    this->ui->RadioButton_Camera1->setChecked(true);
    ui->LineEdit_AcquisitionDeviceName->setText("/dev/ft2232h_ic01_b");
    ui->LineEdit_DataDeviceName->setText("/dev/ft2232h_ic01_a");
    break;
  case 2:
    this->ui->RadioButton_Camera2->setChecked(true);
    ui->LineEdit_AcquisitionDeviceName->setText("/dev/ft2232h_ic02_b");
    ui->LineEdit_DataDeviceName->setText("/dev/ft2232h_ic02_a");
    break;
  default:
    break;
  }
*/
  this->ui->RadioButton_Camera2->setChecked(true);
  ui->LineEdit_AcquisitionDeviceName->setText("/dev/ft2232h_ic02_b");
  ui->LineEdit_DataDeviceName->setText("/dev/ft2232h_ic02_a");

  int nofchips = set.value( "nof-chips", 24).toInt();
  ui->HorizontalSlider_Devices->setValue(nofchips);

  int capacityIndex = set.value( "capacity-index", 3).toInt();
  ui->ComboBox_AcquisitionCapacity->setCurrentIndex(capacityIndex);
  int adcResolution = set.value( "adc-resolution", AdcResolutionType::ADC_16_BIT).toInt();
  switch (adcResolution)
  {
  case AdcResolutionType::ADC_20_BIT:
    ui->RadioButton_Adc20Bit->setChecked(true);
    break;
  case AdcResolutionType::ADC_16_BIT:
  default:
    ui->RadioButton_Adc16Bit->setChecked(true);
    break;
  }
  int intTime = set.value( "integration-time", 1).toInt();
  ui->HorizontalSlider_IntegrationTime->setValue(intTime);

  int samples = set.value("acquisition-samples").toInt();
  ui->HorizontalSlider_Samples->setValue(samples);

  QString spillPrefix = set.value( "spill-prefix", "").toString();
  ui->LineEdit_SpillPrefix->setText(spillPrefix);

  int pedBegin = set.value( "ped-begin", 0).toInt();
  int pedEnd = set.value( "ped-end", 100).toInt();
  int signalBegin = set.value( "signal-begin", 101).toInt();
  int signalEnd = set.value( "signal-end", 200).toInt();
  ui->SpinBox_PedBegin->setValue(pedBegin);
  ui->SpinBox_PedEnd->setValue(pedEnd);
  ui->SpinBox_SignalBegin->setValue(signalBegin);
  ui->SpinBox_SignalEnd->setValue(signalEnd);

  size_t size = static_cast< size_t >(set.beginReadArray("chips"));
  if (size == this->CheckBox_DevicesEnabled.size())
  {
    for (size_t i = 0; i < size; ++i)
    {
      set.setArrayIndex(i);
      bool checked = set.value("checked").toBool();
      this->CheckBox_DevicesEnabled[i]->setChecked(checked);
    }
    set.endArray();
  }
}

void MainWindow::loadICSettings()
{
  // Load JSON descriptor file
  int cameraNumber = this->currentCameraNumber();
  std::string jsonFileName = "ChipsPositions.json";
  switch (cameraNumber)
  {
  case 1:
    jsonFileName = "ChipsPositions1.json";
    break;
  case 2:
    jsonFileName = "ChipsPositions2.json";
    break;
  default:
    break;
  }

  FILE *fp = fopen(jsonFileName.c_str(), "r");
  if (!fp)
  {
    qCritical() << Q_FUNC_INFO << ": Can't open JSON file";
    return;
  }
  const size_t size = 100000;
  std::unique_ptr< char[] > buffer(new char[size]);
  rapidjson::FileReadStream fs(fp, buffer.get(), size);

  rapidjson::Document d;
  if (d.ParseStream(fs).HasParseError())
  {
    qCritical() << Q_FUNC_INFO << ": Can't parse JSON file";
    fclose(fp);
    return;
  }
  fclose(fp);

  const rapidjson::Value& chipChannels = d["ChipChannels"];
  const rapidjson::Value& verticalChips = d["VerticalChips"];
  const rapidjson::Value& horizontalChips = d["HorizontalChips"];
  const rapidjson::Value& chips = d["Chips"];
  const rapidjson::Value& channelSpacingPerSideMM = d["ChannelStepPerSideMM"];

  if (channelSpacingPerSideMM.IsDouble())
  {
    this->channelStepPerSideMM = channelSpacingPerSideMM.GetDouble();
  }

  std::array< int, CHANNELS_PER_CHIP > channels;
  std::array< int, 4 > verticalPlaneChips;
  std::array< int, CHIPS_PER_PLANE > horizontalPlaneChips;
  std::bitset< CHIPS_PER_PLANE * 2 > chipChannelsReverse;
  if (chipChannels.IsArray() && chipChannels.Size() == CHANNELS_PER_CHIP)
  {
    for (rapidjson::SizeType i = 0; i < chipChannels.Size(); i++) // Uses SizeType instead of size_t
    {
      int pos = chipChannels[i].GetInt();
      channels[i] = pos;
    }
  }
  if (verticalChips.IsArray() && verticalChips.Size() == 4)
  {
    for (rapidjson::SizeType i = 0; i < verticalChips.Size(); i++) // Uses SizeType instead of size_t
    {
      verticalPlaneChips[i] = verticalChips[i].GetInt();
    }
  }
  if (horizontalChips.IsArray() && horizontalChips.Size() == 6)
  {
    for (rapidjson::SizeType i = 0; i < horizontalChips.Size(); i++) // Uses SizeType instead of size_t
    {
      horizontalPlaneChips[i] = horizontalChips[i].GetInt();
    }
  }
  if (chips.IsArray())
  {
    for (rapidjson::SizeType i = 0; i < chips.Size(); i++) // Uses SizeType instead of size_t
    {
      int position = -1;
      int reverseChannelsFlag = -1;
      std::string calibrationFileName;
      for (rapidjson::Value::ConstMemberIterator layerIter = chips[i].MemberBegin(); layerIter != chips[i].MemberEnd(); ++layerIter)
      {
        const rapidjson::Value& name = layerIter->name;
        if (name.GetString() == std::string("Position"))
        {
          const rapidjson::Value& positionValue = layerIter->value;
          position = positionValue.GetInt();
        }
        if (name.GetString() == std::string("Name"))
        {
          const rapidjson::Value& nameValue = layerIter->value;
          calibrationFileName = std::string("Chip") + std::string(nameValue.GetString()) + ".json";
        }
        if (name.GetString() == std::string("ReverseChannels"))
        {
          const rapidjson::Value& nameValue = layerIter->value;
          reverseChannelsFlag = nameValue.GetInt();
        }
      }
      if (position != -1 && calibrationFileName.size())
      {
        if (this->loadChipCalibration(calibrationFileName, position))
        {
          /// message here
        }
        else
        {
          /// error message here
        }
      }
      if (position != -1 && reverseChannelsFlag != -1)
      {
        chipChannelsReverse.set(position - 1, static_cast< bool >(reverseChannelsFlag));
      }
    }
  }
  // Create vertical chips channels array depending on channels order (reverse or not)
  int i = 0;
  for (int verticalChip : verticalPlaneChips)
  {
    if (chipChannelsReverse.test(verticalChip - 1))
    {
      for (auto iter = channels.rbegin(); iter != channels.rend(); ++iter)
      {
        this->verticalChipChannelStrips[i++] = std::make_pair( verticalChip, *iter);
      }
    }
    else
    {
      for (auto iter = channels.begin(); iter != channels.end(); ++iter)
      {
        this->verticalChipChannelStrips[i++] = std::make_pair( verticalChip, *iter);
      }
    }
  }
  // Create horizontal chips channels array depending on channels order (reverse or not)
  i = 0;
  for (int horizontalChip : horizontalPlaneChips)
  {
    if (chipChannelsReverse.test(horizontalChip - 1))
    {
      for (auto iter = channels.rbegin(); iter != channels.rend(); ++iter)
      {
        this->horizontalChipChannelStrips[i++] = std::make_pair( horizontalChip, *iter);
      }
    }
    else
    {
      for (auto iter = channels.begin(); iter != channels.end(); ++iter)
      {
        this->horizontalChipChannelStrips[i++] = std::make_pair( horizontalChip, *iter);
      }
    }
  }
}

bool MainWindow::loadChipCalibration(const std::string& jsonFileName, int position)
{
  if ((position < 1) || (position > CHIPS_PER_PLANE * 2))
  {
    return false;
  }
  // Load JSON descriptor file
  FILE *fp = fopen(jsonFileName.c_str(), "r");
  if (!fp)
  {
    qCritical() << Q_FUNC_INFO << ": Can't open JSON file: " << jsonFileName.c_str();
    return false;
  }
  const size_t size = 100000;
  std::unique_ptr< char[] > buffer(new char[size]);
  rapidjson::FileReadStream fs(fp, buffer.get(), size);

  rapidjson::Document d1;
  if (d1.ParseStream(fs).HasParseError())
  {
    qCritical() << Q_FUNC_INFO << ": Can't parse JSON file: " << jsonFileName.c_str();;
    fclose(fp);
    return false;
  }
  fclose(fp);
  const rapidjson::Value& calib = d1["CountPerMilliVoltCalibration"];
  if (calib.IsArray() && (calib.Capacity() == 2))
  {
    const rapidjson::Value& sideA = calib[0];
    const rapidjson::Value& sideB = calib[1];
    // side-A calibration
    for (rapidjson::SizeType pos = 0; pos < sideA.Size(); pos++)
    {
      double value = sideA[pos].GetDouble();
      std::pair< int, int > chipChannelPair( position, pos + 1);
      this->chipChannelCalibrationA[chipChannelPair] = value;
    }
    // side-B calibration
    for (rapidjson::SizeType pos = 0; pos < sideB.Size(); pos++)
    {
      double value = sideB[pos].GetDouble();
      std::pair< int, int > chipChannelPair( position, pos + 1);
      this->chipChannelCalibrationB[chipChannelPair] = value;
    }
  }
  const rapidjson::Value& amplitude = d1["AmplitudeCalibration"];
  if (amplitude.IsArray())
  {
    // Amplitude calibration
    for (rapidjson::SizeType pos = 0; pos < amplitude.Size(); pos++)
    {
      double value = amplitude[pos].GetDouble();
      std::pair< int, int > chipChannelPair( position, pos + 1);
      this->chipChannelCalibrationAmplitude[chipChannelPair] = value;
    }
  }
  return true;
}

void MainWindow::onInitiateDevicesClicked()
{
  this->initiateDevicesCommandsList.clear();

  this->initiateDevicesCommandsList.append(AlteraResetCommand); // Reset ALTERA

  unsigned char buf[BUFFER_SIZE] = {};
  buf[0] = 'O';
  buf[1] = this->ui->HorizontalSlider_Devices->value(); // Number of devices
  buf[2] = 0;
  QByteArray setNumberOfDevices( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  this->initiateDevicesCommandsList.append(setNumberOfDevices);

  unsigned short devsEnabled = this->devicesEnabled();
  buf[0] = 'E';
  buf[1] = devsEnabled & 0xFF; // enabled low bite
  buf[2] = (devsEnabled >> CHAR_BIT) & 0xFF; // enabled high bite
  QByteArray setDevicesEnabled( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  this->initiateDevicesCommandsList.append(setDevicesEnabled); // write enabled devices
/*
  buf[0] = 'M';
  buf[1] = this->ui->HorizontalSlider_Samples->value(); // data
  buf[2] = 0;
  QByteArray setNumberOfSamples( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  this->initiateDevicesCommandsList.append(setNumberOfSamples); // write number of samples
*/
  buf[0] = 'P';
  int v = this->ui->HorizontalSlider_Samples->value();
  buf[1] = v & 0xFF; // data
  buf[2] = (v >> CHAR_BIT) & 0xFF; // data
  QByteArray setNewNumberOfSamples( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  this->initiateDevicesCommandsList.append(setNewNumberOfSamples); // write number of samples

  buf[0] = 'I';
  // data is a intergration time in ms minus 1 is a data written into devices
  buf[1] = (this->ui->HorizontalSlider_IntegrationTime->value() / 2) - 1; // integration time
  buf[2] = 0;
  QByteArray setIntegrationTime( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  this->initiateDevicesCommandsList.append(setIntegrationTime);

  int capacityIndex = this->ui->ComboBox_AcquisitionCapacity->currentIndex();
  std::bitset<3> capacity(capacityIndex);
  std::bitset<8> chipIndex(0);
  chipIndex.set(5, capacity.test(0));
  chipIndex.set(6, capacity.test(1));
  chipIndex.set(7, capacity.test(2));
  buf[0] = 'C';
  buf[1] = static_cast<unsigned char>(chipIndex.to_ulong()); // device capacity
  buf[2] = 0;
  QByteArray setCapacity( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  this->initiateDevicesCommandsList.append(setCapacity);

  buf[0] = 'D';
  buf[1] = this->ui->RadioButton_Adc20Bit->isChecked(); // ADC Resolution (16 or 20 bit)
  buf[2] = 0;
  QByteArray setAdcResolutionCommand( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  this->initiateDevicesCommandsList.append(setAdcResolutionCommand);

  this->initiateDevicesCommandsList.append(WriteCapacitiesCommand); // write chips capacities (write DDC232 configureation register)

  buf[0] = 'A';
  buf[1] = this->ui->CheckBox_ExternalStart->isChecked(); // data
  buf[2] = 0;
  QByteArray beamExtractionInterrupt( reinterpret_cast<char*>(buf), BUFFER_SIZE);
  this->initiateDevicesCommandsList.append(beamExtractionInterrupt); // write beam extraction interrupts

  this->initiateDevicesCommandsList.append(ListChipsEnabledCommand); // write list of chips enabled


  this->initiationProgress->setLabelText("Chips initiation...");
  this->initiationProgress->setRange(0, this->initiateDevicesCommandsList.size());
  this->initiationProgress->setValue(this->initiateDevicesCommandsList.size());
  this->initiationProgress->show();
  QTimer::singleShot( 100, this, SLOT(writeNextCommandFromInitiationList()));
}

void MainWindow::onFirstConnectResponce()
{
  this->lastCommandWritten = FirstContactCommand;
  if (this->acquisitionPort && this->acquisitionPort->isOpen())
  {
    this->acquisitionPort->write(this->lastCommandWritten);
  }
}

void MainWindow::writeNextAgilentCommandFromInitiationList()
{
  if (this->agilentDeviceCommandsList.isEmpty())
  {
    return;
  }

  this->lastAgilentCommandWritten = this->agilentDeviceCommandsList.front();
  if (this->agilentPort && this->agilentPort->isOpen() && !this->lastAgilentCommandWritten.isEmpty())
  {
    this->agilentPort->write(lastAgilentCommandWritten);
  }
}

void MainWindow::writeNextCommandFromInitiationList()
{
  if (this->initiateDevicesCommandsList.isEmpty())
  {
    return;
  }

  this->lastCommandWritten = this->initiateDevicesCommandsList.front();
  if (this->acquisitionPort && this->acquisitionPort->isOpen() && !this->lastCommandWritten.isEmpty())
  {
    this->acquisitionPort->write(lastCommandWritten);
  }
}

void MainWindow::writeLastCommandOnceAgain()
{
  if (this->acquisitionPort && this->acquisitionPort->isOpen() && !this->lastCommandWritten.isEmpty())
  {
    this->acquisitionPort->write(lastCommandWritten);
  }
}

void MainWindow::onSetNextOffset()
{
  if (this->agilentOffsets.size())
  {
    int offset = this->agilentOffsets.front();
    this->setAgilentOffset(offset);
  }
  else
  {
    this->calibrationEnabled = false;
  }
  this->ui->progressBar->setValue(this->agilentOffsets.size());
}

void MainWindow::onAllDevicesEnabledChecked(bool state)
{
  if (state)
  {
    for (QCheckBox* deviceEnabled : CheckBox_DevicesEnabled)
    {
      deviceEnabled->blockSignals(true);
      deviceEnabled->setChecked(true);
      deviceEnabled->blockSignals(false);
    }
  }
}

void MainWindow::onDeviceEnabledCheckBoxChecked(bool state)
{
  QCheckBox* checkBox_DeviceEnabled = qobject_cast< QCheckBox* >(sender());
  std::bitset< CHIPS_PER_PLANE * 2 >allEnabled;
  int pos = -1;
  auto iter = std::find( std::begin(this->CheckBox_DevicesEnabled), std::end(this->CheckBox_DevicesEnabled), checkBox_DeviceEnabled);
  if (iter != this->CheckBox_DevicesEnabled.end())
  {
    pos = static_cast< int >(iter - std::begin(this->CheckBox_DevicesEnabled));
  }
  for (size_t i = 0; i < this->CheckBox_DevicesEnabled.size(); ++i)
  {
    if (this->CheckBox_DevicesEnabled[i] != checkBox_DeviceEnabled)
    {
      allEnabled.set( i, this->CheckBox_DevicesEnabled[i]->isChecked());
    }
  }
  if (pos != -1)
  {
    allEnabled.set( pos, state);
  }
  else
  {
    qCritical() << Q_FUNC_INFO << "pos == -1";
  }

  if (allEnabled.none())
  {
    for (QCheckBox* checkBox : this->CheckBox_DevicesEnabled)
    {
      checkBox->blockSignals(true);
      checkBox->setChecked(true);
      checkBox->blockSignals(false);
    }
    this->ui->CheckBox_AllDevicesEnabled->blockSignals(true);
    this->ui->CheckBox_AllDevicesEnabled->setChecked(true);
    this->ui->CheckBox_AllDevicesEnabled->blockSignals(false);
  }
  else
  {
    this->ui->CheckBox_AllDevicesEnabled->blockSignals(true);
    this->ui->CheckBox_AllDevicesEnabled->setChecked(allEnabled.all());
    this->ui->CheckBox_AllDevicesEnabled->blockSignals(false);
  }
}

unsigned short MainWindow::devicesEnabled() const
{
  std::bitset< CHIPS_PER_PLANE * 2 > enabled;
  for (size_t i = 0; i < this->CheckBox_DevicesEnabled.size(); ++i)
  {
    int pos = this->CheckBox_DevicesEnabled.size() - i - 1;
    enabled.set( i, this->CheckBox_DevicesEnabled[pos]->isChecked());
  }
  return static_cast< unsigned short >(enabled.to_ulong());
}

void MainWindow::onUpdateChannelGraphClicked()
{
//  this->graphChannel->Clear();
  this->getChannelHistSideA()->Reset();
  this->getChannelHistSideB()->Reset();
/*
  for (int i = 0; i < CHANNELS_PER_PLANE; ++i)
  {
    this->getHorizontalStripsGraph()->SetPoint( i, 2 * (i + 1), 0.);
    this->getVerticalStripsGraph()->SetPoint( i, 2 * (i + 1), 0.);
    this->getHorizontalCalibratedStripsGraph()->SetPoint( i, 2 * (i + 1), 0.);
    this->getVerticalCalibratedStripsGraph()->SetPoint( i, 2 * (i + 1), 0.);
  }
*/
  int chipIndex = this->ui->HorizontalSlider_Chip->value() - 1;
  int channelIndex = this->ui->HorizontalSlider_Channel->value() - 1;
  int intTimeMs = this->ui->HorizontalSlider_IntegrationTime->value() / 2; // in ms

  std::vector<int>& sideA = this->channelsCountsA[chipIndex][channelIndex];
  std::vector<int>& sideB = this->channelsCountsB[chipIndex][channelIndex];
  size_t sizeA = sideA.size();
  size_t sizeB = sideB.size();
  if (!sizeA || !sizeB)
  {
    qCritical() << Q_FUNC_INFO << "Chip data size is empty for a chip address: chip number is " << chipIndex;

    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setModal(true);
    msgBox.setWindowTitle(tr("IC control"));
    msgBox.setText(tr("Empty data for a chip %1, channel %2.").arg(chipIndex + 1).arg(channelIndex + 1));
    msgBox.exec();
    return;
  }

  this->channelPad->cd();
  size_t sizeHalfPos = std::min< size_t >(sizeA, sizeB);

  qDebug() << Q_FUNC_INFO << "Minimum size: " << sizeHalfPos;

  if (!this->ui->CheckBox_RawData->isChecked())
  {
    Double_t max = 0, min = 0;

    this->ui->SpinBox_PedBegin->setMinimum(intTimeMs);
    this->ui->SpinBox_PedEnd->setMinimum(intTimeMs);
    this->ui->SpinBox_SignalBegin->setMinimum(intTimeMs);
    this->ui->SpinBox_SignalEnd->setMinimum(intTimeMs);
    this->ui->HorizontalSlider_PedBegin->setMinimum(intTimeMs);
    this->ui->HorizontalSlider_PedEnd->setMinimum(intTimeMs);
    this->ui->HorizontalSlider_SignalBegin->setMinimum(intTimeMs);
    this->ui->HorizontalSlider_SignalEnd->setMinimum(intTimeMs);
    this->ui->SpinBox_PedBegin->setMaximum(intTimeMs * 2 * sizeHalfPos);
    this->ui->SpinBox_PedEnd->setMaximum(intTimeMs * 2 * sizeHalfPos);
    this->ui->SpinBox_SignalBegin->setMaximum(intTimeMs * 2 * sizeHalfPos);
    this->ui->SpinBox_SignalEnd->setMaximum(intTimeMs * 2 * sizeHalfPos);
    this->ui->HorizontalSlider_PedBegin->setMaximum(intTimeMs * 2 * sizeHalfPos);
    this->ui->HorizontalSlider_PedEnd->setMaximum(intTimeMs * 2 * sizeHalfPos);
    this->ui->HorizontalSlider_SignalBegin->setMaximum(intTimeMs * 2 * sizeHalfPos);
    this->ui->HorizontalSlider_SignalEnd->setMaximum(intTimeMs * 2 * sizeHalfPos);

    this->graphChannel->Set(2 * sizeHalfPos);
    this->graphChannel->GetXaxis()->SetTitle("Time (ms)");
    int k = 1;
    for (size_t i = 0; i < sizeHalfPos; i++, k += 2)
    {
      max = std::max< Double_t >( max, Double_t(sideA[i]));
      min = std::min< Double_t >( min, Double_t(sideA[i]));
      max = std::max< Double_t >( max, Double_t(sideB[i]));
      min = std::min< Double_t >( min, Double_t(sideB[i]));
      this->graphChannel->SetPoint( k - 1, Double_t(k * intTimeMs), Double_t(sideA[i]));
      this->graphChannel->SetPoint( k, Double_t((k + 1) * intTimeMs), Double_t(sideB[i]));
      this->getChannelHistSideA()->Fill(Double_t(sideA[i]));
      this->getChannelHistSideB()->Fill(Double_t(sideB[i]));
    }
    this->linePedBegin->SetY2(max);
    this->linePedEnd->SetY2(max);
    this->linePedBegin->SetY1(min);
    this->linePedEnd->SetY1(min);
    this->lineSignalBegin->SetY2(max);
    this->lineSignalEnd->SetY2(max);
    this->lineSignalBegin->SetY1(min);
    this->lineSignalEnd->SetY1(min);
  }
  else
  {
    this->ui->SpinBox_PedBegin->setMinimum(intTimeMs);
    this->ui->SpinBox_PedEnd->setMinimum(intTimeMs);
    this->ui->SpinBox_SignalBegin->setMinimum(intTimeMs);
    this->ui->SpinBox_SignalEnd->setMinimum(intTimeMs);
    this->ui->HorizontalSlider_PedBegin->setMinimum(intTimeMs);
    this->ui->HorizontalSlider_PedEnd->setMinimum(intTimeMs);
    this->ui->HorizontalSlider_SignalBegin->setMinimum(intTimeMs);
    this->ui->HorizontalSlider_SignalEnd->setMinimum(intTimeMs);
    this->ui->SpinBox_PedBegin->setMaximum(intTimeMs * sizeHalfPos);
    this->ui->SpinBox_PedEnd->setMaximum(intTimeMs * sizeHalfPos);
    this->ui->SpinBox_SignalBegin->setMaximum(intTimeMs * sizeHalfPos);
    this->ui->SpinBox_SignalEnd->setMaximum(intTimeMs * sizeHalfPos);
    this->ui->HorizontalSlider_PedBegin->setMaximum(intTimeMs * sizeHalfPos);
    this->ui->HorizontalSlider_PedEnd->setMaximum(intTimeMs * sizeHalfPos);
    this->ui->HorizontalSlider_SignalBegin->setMaximum(intTimeMs * sizeHalfPos);
    this->ui->HorizontalSlider_SignalEnd->setMaximum(intTimeMs * sizeHalfPos);

    Double_t max = 0, min = 0;
    this->graphChannel->Set(2 * sizeHalfPos);
    this->graphChannel->GetXaxis()->SetTitle("Samples * integ. time");
    int k = 1;
    for (size_t i = 0; i < sizeHalfPos; i++, k++)
    {
      max = std::max< Double_t >( max, Double_t(sideA[i]));
      min = std::min< Double_t >( min, Double_t(sideA[i]));
      this->graphChannel->SetPoint( k - 1, Double_t(k * intTimeMs), Double_t(sideA[i]));
      this->getChannelHistSideA()->Fill(Double_t(sideA[i]));
    }
    for (size_t i = 0; i < sizeHalfPos; i++, k++)
    {
      max = std::max< Double_t >( max, Double_t(sideB[i]));
      min = std::min< Double_t >( min, Double_t(sideB[i]));
      this->graphChannel->SetPoint( k - 1, Double_t(k * intTimeMs), Double_t(sideB[i]));
      this->getChannelHistSideB()->Fill(Double_t(sideB[i]));
    }
  }

  this->channelHistPad[SIDE_A]->Modified();
  this->channelHistPad[SIDE_A]->Update();
  this->channelHistPad[SIDE_B]->Modified();
  this->channelHistPad[SIDE_B]->Update();
  this->channelPad->Modified();
  this->channelPad->Update();
}


void MainWindow::onOpenRootFileClicked()
{
  QFileDialog* dialog = new QFileDialog( this, tr("Open ROOT File..."));
  QStringList fileNames;

  dialog->setAcceptMode(QFileDialog::AcceptOpen);
  dialog->setFileMode(QFileDialog::ExistingFile);

#if QT_VERSION >= 0x050000
  filters << tr("ROOT Files *.root (*.root)");
  dialog->setNameFilters(filters);
#elif (QT_VERSION >= 0x040000 && QT_VERSION < 0x050000)
  dialog->setFilter(tr("ROOT Files *.root (*.root)"));
#endif

  if (dialog->exec())
  {
    fileNames = dialog->selectedFiles();

    if (!fileNames.isEmpty())
    {
      rootFileName = fileNames[0];
    }
  }
  delete dialog;

  if (rootFileName.isEmpty())
  {
    return;
  }

  this->ui->ListWidget_Spills->clear();

  std::string fname = rootFileName.toStdString();
  TFile* f = TFile::Open(fname.c_str());
  TIter keyList(f->GetListOfKeys());
  TKey* key = nullptr;
  while ((key = dynamic_cast<TKey*>(keyList())))
  {
    TClass* cl = gROOT->GetClass(key->GetClassName());
    if (cl && !cl->InheritsFrom("TTree"))
    {
      continue;
    }

    TTree *spillTree = dynamic_cast<TTree*>(key->ReadObj());
    if (spillTree)
    {
      const char* name = spillTree->GetName();
/*
      QByteArray arr(name);
      if (arr.startsWith("tangent_"))
      {
        int numberOfChannels;
        double sideA[CHANNELS_PER_CHIP] = {};
        double sideB[CHANNELS_PER_CHIP] = {};
        spillTree->SetBranchAddress("channelsPerChip", &numberOfChannels);
        spillTree->SetBranchAddress("tanSideA", sideA);
        spillTree->SetBranchAddress("tanSideB", sideB);
        Int_t nentries = static_cast<Int_t>(spillTree->GetEntries());
        qDebug() << Q_FUNC_INFO << QString(name);
        for (Int_t i = 0; i < nentries; i++)
        {
          spillTree->GetEntry(i);
          for (int j = 0; j < CHANNELS_PER_CHIP; ++j)
          {
            qDebug() << Q_FUNC_INFO << j + 1 << ' ' << sideA[j] << ' ' << sideB[j];
          }
        }
      }
*/
      ui->ListWidget_Spills->addItem(QString(name));
    }
  }
}

void MainWindow::onProcessSelectedItemsClicked()
{
  if (rootFileName.isEmpty())
  {
    return;
  }
  std::string rootStdName = rootFileName.toStdString();
  TFile* f = TFile::Open(rootStdName.c_str());

  QList<QListWidgetItem*> selectedItems = ui->ListWidget_Spills->selectedItems();
  ui->Label_NumberOfSpills->setText(tr("%1").arg(selectedItems.size()));

  for (QListWidgetItem* item : selectedItems)
  {
    struct ChamberResponse tmpResponse;

    ULong64_t bufferSize = 0;
    std::vector< char > buffer;
    std::vector< char >* bufferPtr = &buffer;

    ULong64_t chipsAcquiredSize = 0;
    std::vector< int > chipsAcquired;
    std::vector< int >* chipsAcquiredPtr = &chipsAcquired;

    unsigned int mode = -1;
    int adcMode = -1;
    if (!item)
    {
      continue;
    }
    QString treeName = item->text();
    std::string treeStdName = treeName.toStdString();
    TTree* spillTree = dynamic_cast< TTree* >(f->Get(treeStdName.c_str()));

    if (spillTree)
    {
      spillTree->SetBranchAddress("respChipsEnabled", &tmpResponse.ChipsEnabled);
      spillTree->SetBranchAddress("respChipsEnabledCode", &tmpResponse.ChipsEnabledCode);
      spillTree->SetBranchAddress("respIntTime", &tmpResponse.IntegrationTimeCode);
      spillTree->SetBranchAddress("respCapacity", &tmpResponse.CapacityCode);
      spillTree->SetBranchAddress("respExtStart", &tmpResponse.ExternalStartState);
      spillTree->SetBranchAddress("respAdcMode", &tmpResponse.AdcMode);
      spillTree->SetBranchAddress("mode", &mode);
      spillTree->SetBranchAddress("adcMode", &adcMode);
      spillTree->SetBranchAddress("bufferSize", &bufferSize);
      spillTree->SetBranchAddress("bufferVector", &bufferPtr);
      spillTree->SetBranchAddress("chipsAcquired", &chipsAcquiredSize);
      spillTree->SetBranchAddress("chipsAcquiredVector", &chipsAcquiredPtr);

      Int_t nentries = static_cast<Int_t>(spillTree->GetEntries());

      for (Int_t i = 0; i < nentries; i++)
      {
        spillTree->GetEntry(i);
        if (bufferSize && bufferSize == buffer.size())
        {
          this->acquisitionDataBuffer.resize(bufferSize);
          std::copy( buffer.begin(), buffer.end(), this->acquisitionDataBuffer.begin());

          switch (tmpResponse.AdcMode)
          {
          case 16:
            this->ui->RadioButton_Adc16Bit->setChecked(true);
            break;
          case 20:
            this->ui->RadioButton_Adc20Bit->setChecked(true);
            break;
          default:
            break;
          }

          int integrationTimeCode = mode & 0x0F;
          int capacityCode = mode >> 4;
          if (integrationTimeCode == tmpResponse.IntegrationTimeCode)
          {
            this->ui->HorizontalSlider_IntegrationTime->setValue((integrationTimeCode + 1) * 2);
          }
          if (capacityCode == tmpResponse.CapacityCode)
          {
            this->ui->ComboBox_AcquisitionCapacity->setCurrentIndex(capacityCode);
          }
          this->ui->CheckBox_ExternalStart->setChecked(tmpResponse.ExternalStartState);

          qDebug() << Q_FUNC_INFO << "Item name: " << item->text();
          this->onProcessRawDataClicked();
          if (this->chipsAddresses.size() == size_t(tmpResponse.ChipsEnabled))
          {
            this->chamberResponse = tmpResponse;
            qDebug() << Q_FUNC_INFO << "Number of enabled chips are correct";
            this->onProcessSpillChannelsCountsClicked();
          }
          this->acquisitionDataBuffer.clear();
        }
      }
    }
  }
  this->hist2Pad[ORIENTATION_VERTICAL]->Modified();
  this->hist2Pad[ORIENTATION_VERTICAL]->Update();
  this->graphPad[ORIENTATION_VERTICAL]->Modified();
  this->graphPad[ORIENTATION_VERTICAL]->Update();
  this->hist2Pad[ORIENTATION_HORIZONTAL]->Modified();
  this->hist2Pad[ORIENTATION_HORIZONTAL]->Update();
  this->graphPad[ORIENTATION_HORIZONTAL]->Modified();
  this->graphPad[ORIENTATION_HORIZONTAL]->Update();
  this->padFit[ORIENTATION_VERTICAL]->Modified();
  this->padFit[ORIENTATION_VERTICAL]->Update();
  this->padFit[ORIENTATION_HORIZONTAL]->Modified();
  this->padFit[ORIENTATION_HORIZONTAL]->Update();
}

void MainWindow::onClearSpillListClicked()
{
  this->ui->ListWidget_Spills->clear();
  this->rootFileName.clear();
}

void MainWindow::onPedestalsBeginClicked(int v)
{
  this->channelPad->cd();
  this->linePedBegin->SetX1(v);
  this->linePedBegin->SetX2(v);
  this->channelPad->Modified();
  this->channelPad->Update();
}

void MainWindow::onPedestalsEndClicked(int v)
{
  this->channelPad->cd();
  this->linePedEnd->SetX1(v);
  this->linePedEnd->SetX2(v);
  this->channelPad->Modified();
  this->channelPad->Update();
}

void MainWindow::onSignalBeginClicked(int v)
{
  this->channelPad->cd();
  this->lineSignalBegin->SetX1(v);
  this->lineSignalBegin->SetX2(v);
  this->channelPad->Modified();
  this->channelPad->Update();
}

void MainWindow::onSignalEndClicked(int v)
{
  this->channelPad->cd();
  this->lineSignalEnd->SetX1(v);
  this->lineSignalEnd->SetX2(v);
  this->channelPad->Modified();
  this->channelPad->Update();
}

void MainWindow::onInitiateDevicesStopClicked()
{
}

void MainWindow::onInitiateDevicesFinished(int)
{
}

void MainWindow::onStartIterationAcquisitionClicked()
{
  if (this->calibrationEnabled)
  {
    this->ui->progressBar->setValue(0);
    this->calibrationEnabled = false;
    this->calibrationChannelsCounts.clear();
    this->agilentOffsets.clear();
    return;
  }

  this->calibrationEnabled = true;
  int offBegin = this->ui->SpinBox_OffsetBegin->value();
  int offEnd = this->ui->SpinBox_OffsetEnd->value();
  int offStep = this->ui->SpinBox_OffsetStep->value();
  this->ui->SpinBox_TanOffsetBegin->setRange( offBegin, offEnd);
  this->ui->SpinBox_TanOffsetEnd->setRange( offBegin, offEnd);
  this->ui->SpinBox_TanOffsetBegin->setSingleStep(offStep);
  this->ui->SpinBox_TanOffsetEnd->setSingleStep(offStep);
  this->ui->LineEdit_SpillPrefix->setText(tr("Calibration_%1_%2_%3").arg(offBegin).arg(offEnd).arg(offStep));
  this->agilentOffsets.clear();
  this->calibrationChannelsCounts.clear();
  if (this->ui->SpinBox_OffsetBegin->value() >= this->ui->SpinBox_OffsetEnd->value())
  {
    return;
  }
  for (int i = offBegin; i <= offEnd; i += offStep)
  {
    this->agilentOffsets.push_back(i);
  }
  this->ui->progressBar->setRange(0, this->agilentOffsets.size());
  QTimer::singleShot( 100, this, SLOT(onSetNextOffset()));
}

bool MainWindow::checkLastCommandWrittenAndRespose()
{
  if (this->acquisitionResponseBuffer.isEmpty() || this->lastCommandWritten.isEmpty())
  {
    return false;
  }

  const char* responseData = this->acquisitionResponseBuffer.data();
  const char* lastWrittenData = this->lastCommandWritten.data();

  if (this->acquisitionResponseBuffer.endsWith("OK") || this->acquisitionResponseBuffer.endsWith("Welcome"))
  {
    const std::string commandHeaders("GMRHAOCIDSELP");
    char comHeader = responseData[0];
    auto CheckHeaderOK = [comHeader](char headerCharacter) -> bool { return comHeader == headerCharacter; };
    auto resComHeader = std::find_if(std::begin(commandHeaders), std::end(commandHeaders), CheckHeaderOK);
    comHeader = lastWrittenData[0];
    auto writtenComHeader = std::find_if(std::begin(commandHeaders), std::end(commandHeaders), CheckHeaderOK);
    if (resComHeader != std::end(commandHeaders) && writtenComHeader != std::end(commandHeaders) && *resComHeader == *writtenComHeader)
    {
      return true;
    }
  }

  if (this->acquisitionResponseBuffer.endsWith("NO"))
  {
    const std::string commandHeaders("OMIEP");
    char comHeader = responseData[0];
    auto CheckHeaderNO = [comHeader](char headerCharacter) -> bool { return comHeader == headerCharacter; };

    auto resComHeader = std::find_if(std::begin(commandHeaders), std::end(commandHeaders), CheckHeaderNO);
    comHeader = lastWrittenData[0];
    auto writtenComHeader = std::find_if(std::begin(commandHeaders), std::end(commandHeaders), CheckHeaderNO);
    if (resComHeader != std::end(commandHeaders) && writtenComHeader != std::end(commandHeaders) && *resComHeader == *writtenComHeader)
    {
      qCritical() << Q_FUNC_INFO << "Last command with header \"" << comHeader << "\" : parameter isn't set";
    }
  }
  return false;
}

bool MainWindow::checkLastCommandWrittenAndRespose(const QByteArray& responseBuffer)
{
  if (responseBuffer.isEmpty() || this->lastCommandWritten.isEmpty())
  {
    return false;
  }

  const char* responseData = responseBuffer.data();
  const char* lastWrittenData = this->lastCommandWritten.data();

  if (responseBuffer.endsWith("OK") || responseBuffer.endsWith("Welcome"))
  {
    const std::string commandHeaders("GMRHAOCIDSELP");
    char comHeader = responseData[0];
    auto CheckHeaderOK = [comHeader](char headerCharacter) -> bool { return comHeader == headerCharacter; };
    auto resComHeader = std::find_if(std::begin(commandHeaders), std::end(commandHeaders), CheckHeaderOK);
    comHeader = lastWrittenData[0];
    auto writtenComHeader = std::find_if(std::begin(commandHeaders), std::end(commandHeaders), CheckHeaderOK);
    if (resComHeader != std::end(commandHeaders) && writtenComHeader != std::end(commandHeaders) && *resComHeader == *writtenComHeader)
    {
      return true;
    }
  }

  if (responseBuffer.endsWith("NO"))
  {
    const std::string commandHeaders("OMIEP");
    char comHeader = responseData[0];
    auto CheckHeaderNO = [comHeader](char headerCharacter) -> bool { return comHeader == headerCharacter; };

    auto resComHeader = std::find_if(std::begin(commandHeaders), std::end(commandHeaders), CheckHeaderNO);
    comHeader = lastWrittenData[0];
    auto writtenComHeader = std::find_if(std::begin(commandHeaders), std::end(commandHeaders), CheckHeaderNO);
    if (resComHeader != std::end(commandHeaders) && writtenComHeader != std::end(commandHeaders) && *resComHeader == *writtenComHeader)
    {
      qCritical() << Q_FUNC_INFO << "Last command with header \"" << comHeader << "\" : parameter isn't set";
    }
  }
  return false;
}

bool MainWindow::fitSpillData(std::ofstream& ofs, const std::map< int, double >& horizProfile, const std::map< int, double >& vertProfile)
{
  std::vector<double> h, v;
  for (auto horizPair : horizProfile)
  {
    h.push_back(horizPair.second);
  }
  for (auto vertPair : vertProfile)
  {
    v.push_back(vertPair.second);
  }
  double hv = 0., vv = 0.;
  auto horizMaxIter = std::max_element( h.begin(), h.end());
  if (horizMaxIter != h.end())
  {
    hv = *horizMaxIter;
  }
  auto vertMaxIter = std::max_element( v.begin(), v.end());
  if (vertMaxIter != v.end())
  {
    vv = *vertMaxIter;
  }

  if (hv <= 0.12 / 4. || vv <= 0.12 / 4.)
  {
    return false;
  }

  this->ui->RootCanvas_Fit->getCanvas()->cd(1);
  this->padFit[ORIENTATION_HORIZONTAL]->cd();
  Double_t fitVerProfParams[3] = { hv, 103.8, 11.26 };
  TF1* verProfFit = new TF1( "fitVerProf", "gaus", 65, 145);
  verProfFit->SetParameters(fitVerProfParams);
  verProfFit->SetLineWidth(2.5);
  verProfFit->SetLineColor(kRed);
  verProfFit->SetLineStyle(1);
  this->graphFit[ORIENTATION_HORIZONTAL]->Fit( "fitVerProf", "RB0", "ep");
  verProfFit->SetNpx(400);
//  verProfFit->Draw("LSAME");
  Double_t* params = verProfFit->GetParameters();
  qDebug() << Q_FUNC_INFO << "Vertical profile fit parameters. Constant " << params[0] << ", Mean: " << params[1] << ", Deviance: " << params[2];
  ofs << params[0] << ' ' << params[1] << ' ' << params[2] << ' ';
  this->ui->RootCanvas_Fit->getCanvas()->cd(2);
  this->padFit[ORIENTATION_VERTICAL]->cd();
  Double_t fitHorProfParams[3] = { vv, 79.3, 10.1 };
  TF1* horProfFit = new TF1( "fitHorProf", "gaus", 45, 115);
  horProfFit->SetParameters(fitHorProfParams);
  horProfFit->SetLineWidth(2.5);
  horProfFit->SetLineColor(kRed);
  horProfFit->SetLineStyle(1);
  this->graphFit[ORIENTATION_VERTICAL]->Fit( "fitHorProf", "RB0", "ep");
  horProfFit->SetNpx(400);
//  horProfFit->Draw("LSAME");
  params = horProfFit->GetParameters();
  qDebug() << Q_FUNC_INFO << "Horizontal profile fit parameters. Constant " << params[0] << ", Mean: " << params[1] << ", Deviance: " << params[2];
  ofs << params[0] << ' ' << params[1] << ' ' << params[2] << std::endl;
  delete verProfFit;
  delete horProfFit;

  return true;
}

void MainWindow::onFitParametersClicked()
{
  this->ui->RootCanvas_Fit->getCanvas()->cd(1);
  this->padFit[ORIENTATION_HORIZONTAL]->cd();
  Double_t fitVerProfParams[3] = { 0.228, 103.8, 11.26 };
  TF1* fit2 = new TF1( "fitVerProf", "gaus", 65, 145);
  fit2->SetParameters(fitVerProfParams);
  fit2->SetLineWidth(2.5);
  fit2->SetLineColor(kRed);
  fit2->SetLineStyle(1);
  this->graphFit[ORIENTATION_HORIZONTAL]->Fit( "fitVerProf", "RB0", "ep");
  fit2->SetNpx(400);
  fit2->Draw("LSAME");
  qDebug() << Q_FUNC_INFO << fit2->Integral( 70., 136) << " " << fit2->Integral( 102.8, 104.8);

  this->ui->RootCanvas_Fit->getCanvas()->cd(2);
  this->padFit[ORIENTATION_VERTICAL]->cd();
  Double_t fitHorProfParams[3] = { 0.218, 79.3, 10.1 };
  TF1* fit = new TF1( "fitHorProf", "gaus", 45, 115);
  fit->SetParameters(fitHorProfParams);
  fit->SetLineWidth(2.5);
  fit->SetLineColor(kRed);
  fit->SetLineStyle(1);
  this->graphFit[ORIENTATION_VERTICAL]->Fit( "fitHorProf", "RB0", "ep");
  fit->SetNpx(400);
  fit->Draw("LSAME");
  qDebug() << Q_FUNC_INFO << fit->Integral( 49., 109) << " " << fit->Integral( 78.3, 80.3);

  this->padFit[ORIENTATION_VERTICAL]->Modified();
  this->padFit[ORIENTATION_VERTICAL]->Update();
  this->padFit[ORIENTATION_HORIZONTAL]->Modified();
  this->padFit[ORIENTATION_HORIZONTAL]->Update();
}

void MainWindow::onClearHistogramsClicked()
{
  this->ui->RootCanvas_VerticalStrips->getCanvas()->cd(1);
  this->hist2Pad[ORIENTATION_HORIZONTAL]->cd();
  this->getHorizontalStripsHist()->Reset();
  this->hist2Pad[ORIENTATION_HORIZONTAL]->Modified();
  this->hist2Pad[ORIENTATION_HORIZONTAL]->Update();

  this->ui->RootCanvas_HorizontalStrips->getCanvas()->cd(1);
  this->hist2Pad[ORIENTATION_VERTICAL]->cd();
  this->getVerticalStripsHist()->Reset();
  this->hist2Pad[ORIENTATION_VERTICAL]->Modified();
  this->hist2Pad[ORIENTATION_VERTICAL]->Update();
}

void MainWindow::onCalibrationClicked()
{
  int channelIndex = this->ui->HorizontalSlider_CalibrationChannel->value() - 1;

  int calibrationSize = this->calibrationChannelsCounts.size();
  qDebug() << Q_FUNC_INFO << "Calibration size: " << calibrationSize;
  this->calibrationGraph->Set(calibrationSize);
  this->calibrationGraph->GetXaxis()->SetTitle("Offset (mV)");

  this->calibrationPad->cd();

  int intTimeMs = this->ui->HorizontalSlider_IntegrationTime->value() / 2;
  qDebug() << Q_FUNC_INFO << "Integration time index: " << intTimeMs;
  int pedBegin = static_cast<int>(this->ui->SpinBox_PedBegin->value() / (2 * intTimeMs));
  int pedEnd = static_cast<int>(this->ui->SpinBox_PedEnd->value() / (2 * intTimeMs));
  int sigBegin = static_cast<int>(this->ui->SpinBox_SignalBegin->value() / (2 * intTimeMs));
  int sigEnd = static_cast<int>(this->ui->SpinBox_SignalEnd->value() / (2 * intTimeMs));

  if (this->ui->CheckBox_RawData->isChecked())
  {
    pedBegin = static_cast<int>(this->ui->SpinBox_PedBegin->value() / intTimeMs);
    pedEnd = static_cast<int>(this->ui->SpinBox_PedEnd->value() / intTimeMs);
    sigBegin = static_cast<int>(this->ui->SpinBox_SignalBegin->value() / intTimeMs);
    sigEnd = static_cast<int>(this->ui->SpinBox_SignalEnd->value() / intTimeMs);
  }
  qDebug() << Q_FUNC_INFO << pedBegin << ' ' << pedEnd << ' ' << sigBegin << ' ' << sigEnd;

  int i = 0;
  for (auto cIter = this->calibrationChannelsCounts.begin(); cIter != this->calibrationChannelsCounts.end(); ++cIter)
  {
    std::pair< std::vector<int>, std::vector<int> >& pair = cIter->second;
    std::vector<int>& sideA = pair.first;
    std::vector<int>& sideB = pair.second;
    size_t sizeA = sideA.size();
    size_t sizeB = sideB.size();
    if (!sizeA || !sizeB)
    {
      qCritical() << Q_FUNC_INFO << "Chip data size is empty for a calibration";
      return;
    }

    std::vector<int> b, a;
    MeanDispAccumType statPedB;
    MeanDispAccumType statSigB;
    MeanDispAccumType statPedA;
    MeanDispAccumType statSigA;
    for (size_t j = 0; j < sizeB; j += CHANNELS_PER_CHIP)
    {
      b.push_back(sideB[j + channelIndex]);
    }
    for (size_t j = 0; j < sizeA; j += CHANNELS_PER_CHIP)
    {
      a.push_back(sideA[j + channelIndex]);
    }
    for (int j = pedBegin; j < pedEnd; ++j)
    {
      statPedB(b[j]);
      statPedA(a[j]);
    }
    for (int j = sigBegin; j < sigEnd; ++j)
    {
      statSigB(b[j]);
      statSigA(a[j]);
    }

    ChannelInfo stripInfo;
    stripInfo.pedMeanA = boost::accumulators::mean(statPedA);
    stripInfo.pedMeanB = boost::accumulators::mean(statPedB);
    stripInfo.pedMom2A = boost::accumulators::moment<2>(statPedA);
    stripInfo.pedMom2B = boost::accumulators::moment<2>(statPedB);
    stripInfo.sigMeanA = boost::accumulators::mean(statSigA);
    stripInfo.sigMeanB = boost::accumulators::mean(statSigB);
    stripInfo.sigMom2A = boost::accumulators::moment<2>(statSigA);
    stripInfo.sigMom2B = boost::accumulators::moment<2>(statSigB);
    stripInfo.sigCountA = boost::accumulators::count(statSigA);
    stripInfo.sigCountB = boost::accumulators::count(statSigB);
    stripInfo.sigSumA = boost::accumulators::sum(statSigA);
    stripInfo.sigSumB = boost::accumulators::sum(statSigB);

//    double signalA = stripInfo.sigSumA - stripInfo.sigCountA * stripInfo.pedMeanA;
//    double signalB = stripInfo.sigSumB - stripInfo.sigCountB * stripInfo.pedMeanB;
//    double channelSignal = (signalA + signalB) / 2.;

//    double dispPedA = stripInfo.pedMom2A - stripInfo.pedMeanA * stripInfo.pedMeanA;
//    double dispPedB = stripInfo.pedMom2B - stripInfo.pedMeanB * stripInfo.pedMeanB;
//    double dispSigA = stripInfo.sigMom2A - stripInfo.sigMeanA * stripInfo.sigMeanA;
//    double dispSigB = stripInfo.sigMom2B - stripInfo.sigMeanB * stripInfo.sigMeanB;

//    size_t size = std::min< size_t >(sizeA, sizeB);
//    int sizeHalfPos = size / CHANNELS_PER_CHIP;
//    qDebug() << Q_FUNC_INFO << "Offset value: " << cIter->first << ", Size: " << size << ", Graph side size: " << sizeHalfPos;
    this->calibrationGraph->SetPoint( i++, Double_t(cIter->first), (stripInfo.sigMeanA + stripInfo.sigMeanB) / 2.);
  }
  this->calibrationPad->Modified();
  this->calibrationPad->Update();
}

void MainWindow::onCalibrateClicked()
{
//  QList<QListWidgetItem*> selectedItems = ui->ListWidget_Spills->selectedItems();
//  ui->Label_NumberOfSpills->setText(tr("%1").arg(selectedItems.size()));

//  std::map< std::pair< int, int >, std::vector< double > > data;
//  for (QListWidgetItem* item : selectedItems)
//  {
    //int ind = ui->ListWidget_Spills->row(item);
//  std::ofstream file("intCalibrationHorizontal.txt");
/*
    int ind = ui->ListWidget_Spills->currentRow();
    if (ind == -1)
    {
      return;
    }
    std::array< int, 4 > pos = HorizontalStripsCalibration.at(ind);
    if (pos[0] == 0 && pos[1] == 0 && pos[2] == 0 && pos[3] == 0)
    {
      return;
    }

    TGraphErrors* grap = this->getHorizontalStripsGraph();
    Double_t y;
    Double_t x;
    for (int i = pos[0]; i <= pos[1]; ++i)
    {
      std::pair< int, int > chipStrip = HorizontalChipChannelStrips[i];
      Int_t res = grap->GetPoint(i, x, y);
      Q_UNUSED(res);
      std::vector< double >& vec = AmplitudeCalibrationMap.at(chipStrip);
      vec.push_back(static_cast< double >(y));
//      qDebug() << Q_FUNC_INFO << "Chip: " << chipStrip.first << ", strip: " << chipStrip.second << ", res: " << res << ", value: " << y << '\n';
    }
    for (int i = pos[2]; i <= pos[3]; ++i)
    {
      std::pair< int, int > chipStrip = HorizontalChipChannelStrips[i];
      Int_t res = grap->GetPoint(i, x, y);
      Q_UNUSED(res);
      std::vector< double >& vec = AmplitudeCalibrationMap.at(chipStrip);
      vec.push_back(static_cast< double >(y));
//      qDebug() << Q_FUNC_INFO << "Chip: " << chipStrip.first << ", strip: " << chipStrip.second << ", res: " << res << ", value: " << y << '\n';
    }
//  }

  for(auto pair : AmplitudeCalibrationMap)
  {
    std::pair< int, int > p = pair.first;
    std::vector< double >& v = pair.second;
    file << p.first << ' ' << p.second << ' ';
    for (double value : v)
    {
      file << value << ' ';
    }
    file << '\n';
  }
  file.close();
*/
  std::map< std::pair< int, int >, Double_t > dataMap;
  for (int i = 0; i < CHANNELS_PER_PLANE; ++i)
  {
    std::pair< int, int > chipStripHorizontal = this->horizontalChipChannelStrips[i];
    std::pair< int, int > chipStripVertical = this->verticalChipChannelStrips[i];
    Double_t xV, yV, xH, yH;
    Int_t pos = this->getVerticalCalibratedStripsGraph()->GetPoint( i, xV, yV);
    pos = this->getHorizontalCalibratedStripsGraph()->GetPoint( i, xH, yH);
    Q_UNUSED(pos);
    dataMap.insert({ chipStripHorizontal, yH });
    dataMap.insert({ chipStripVertical, yV });
  }
  std::ofstream file("CalibFull.txt");
  for(auto pair : dataMap)
  {
    std::pair< int, int > p = pair.first;
    Double_t v = pair.second;
    file << p.first << ' ' << p.second << ' ' << v << '\n';
  }
  file.close();
}

void MainWindow::onTangentCalculationClicked()
{
  int calcBegin = this->ui->SpinBox_TanOffsetBegin->value();
  int calcEnd = this->ui->SpinBox_TanOffsetEnd->value();
//  int posBegin = (calcBegin - this->ui->SpinBox_TanOffsetBegin->minimum()) / this->ui->SpinBox_TanOffsetBegin->singleStep();
//  int posEnd = (calcEnd - this->ui->SpinBox_TanOffsetEnd->minimum()) / this->ui->SpinBox_TanOffsetEnd->singleStep();

  this->ui->TableWidget_ChannelsTangent->setRowCount(CHANNELS_PER_CHIP);
  double tanSideA[CHANNELS_PER_CHIP] = {}, tanSideB[CHANNELS_PER_CHIP] = {};
  for (int channelIndex = 0; channelIndex < CHANNELS_PER_CHIP; ++channelIndex)
  {
    std::pair< double, double > resA( -1., -1);
    std::pair< double, double > resB( -1., -1);
    int intTimeMs = this->ui->HorizontalSlider_IntegrationTime->value() / 2;
    int pedBegin = static_cast<int>(this->ui->SpinBox_PedBegin->value() / (2 * intTimeMs));
    int pedEnd = static_cast<int>(this->ui->SpinBox_PedEnd->value() / (2 * intTimeMs));
    int sigBegin = static_cast<int>(this->ui->SpinBox_SignalBegin->value() / (2 * intTimeMs));
    int sigEnd = static_cast<int>(this->ui->SpinBox_SignalEnd->value() / (2 * intTimeMs));

    if (this->ui->CheckBox_RawData->isChecked())
    {
      pedBegin = static_cast<int>(this->ui->SpinBox_PedBegin->value() / intTimeMs);
      pedEnd = static_cast<int>(this->ui->SpinBox_PedEnd->value() / intTimeMs);
      sigBegin = static_cast<int>(this->ui->SpinBox_SignalBegin->value() / intTimeMs);
      sigEnd = static_cast<int>(this->ui->SpinBox_SignalEnd->value() / intTimeMs);
    }
    for (auto cIter = this->calibrationChannelsCounts.begin(); cIter != this->calibrationChannelsCounts.end(); ++cIter)
    {
      std::pair< std::vector<int>, std::vector<int> >& pair = cIter->second;
      std::vector<int>& sideA = pair.first;
      std::vector<int>& sideB = pair.second;
      size_t sizeA = sideA.size();
      size_t sizeB = sideB.size();
      if (!sizeA || !sizeB)
      {
        qCritical() << Q_FUNC_INFO << "Chip data size is empty for a calibration";
        return;
      }
      qDebug() << Q_FUNC_INFO << cIter->first << ' ' << calcBegin << ' ' << calcEnd;
      if (cIter->first == calcBegin || cIter->first == calcEnd)
      {
        std::vector<int> b, a;
        MeanDispAccumType statPedB;
        MeanDispAccumType statSigB;
        MeanDispAccumType statPedA;
        MeanDispAccumType statSigA;
        for (size_t j = 0; j < sizeB; j += CHANNELS_PER_CHIP)
        {
          b.push_back(sideB[j + channelIndex]);
        }
        for (size_t j = 0; j < sizeA; j += CHANNELS_PER_CHIP)
        {
          a.push_back(sideA[j + channelIndex]);
        }
        for (int j = pedBegin; j < pedEnd; ++j)
        {
          statPedB(b[j]);
          statPedA(a[j]);
        }
        for (int j = sigBegin; j < sigEnd; ++j)
        {
          statSigB(b[j]);
          statSigA(a[j]);
        }

        ChannelInfo stripInfo;
        stripInfo.pedMeanA = boost::accumulators::mean(statPedA);
        stripInfo.pedMeanB = boost::accumulators::mean(statPedB);
        stripInfo.pedMom2A = boost::accumulators::moment<2>(statPedA);
        stripInfo.pedMom2B = boost::accumulators::moment<2>(statPedB);
        stripInfo.sigMeanA = boost::accumulators::mean(statSigA);
        stripInfo.sigMeanB = boost::accumulators::mean(statSigB);
        stripInfo.sigMom2A = boost::accumulators::moment<2>(statSigA);
        stripInfo.sigMom2B = boost::accumulators::moment<2>(statSigB);
        stripInfo.sigCountA = boost::accumulators::count(statSigA);
        stripInfo.sigCountB = boost::accumulators::count(statSigB);
        stripInfo.sigSumA = boost::accumulators::sum(statSigA);
        stripInfo.sigSumB = boost::accumulators::sum(statSigB);

    //  double signalA = stripInfo.sigSumA - stripInfo.sigCountA * stripInfo.pedMeanA;
    //  double signalB = stripInfo.sigSumB - stripInfo.sigCountB * stripInfo.pedMeanB;
    //  double channelSignal = (signalA + signalB) / 2.;

    //  double dispPedA = stripInfo.pedMom2A - stripInfo.pedMeanA * stripInfo.pedMeanA;
    //  double dispPedB = stripInfo.pedMom2B - stripInfo.pedMeanB * stripInfo.pedMeanB;
    //  double dispSigA = stripInfo.sigMom2A - stripInfo.sigMeanA * stripInfo.sigMeanA;
    //  double dispSigB = stripInfo.sigMom2B - stripInfo.sigMeanB * stripInfo.sigMeanB;
        if (cIter->first == calcBegin)
        {
          resA.first = stripInfo.sigMeanA;
          resB.first = stripInfo.sigMeanB;
        }
        else if (cIter->first == calcEnd)
        {
          resA.second = stripInfo.sigMeanA;
          resB.second = stripInfo.sigMeanB;
        }
      }
    }
    tanSideA[channelIndex] = (resA.second - resA.first) / double(calcEnd - calcBegin);
    QTableWidgetItem* item = new QTableWidgetItem(tr("%1").arg(tanSideA[channelIndex]));
    this->ui->TableWidget_ChannelsTangent->setItem( channelIndex, 0, item);
    tanSideB[channelIndex] = (resB.second - resB.first) / double(calcEnd - calcBegin);
    item = new QTableWidgetItem(tr("%1").arg(tanSideB[channelIndex]));
    this->ui->TableWidget_ChannelsTangent->setItem( channelIndex, 1, item);
  }

  for (auto cIter = this->calibrationChannelsCounts.begin(); cIter != this->calibrationChannelsCounts.end(); ++cIter)
  {
    int offset = cIter->first;
    std::pair< std::vector<int>, std::vector<int> >& pair = cIter->second;
    std::vector<int>& sideA = pair.first;
    std::vector<int>& sideB = pair.second;
    this->storeCalibrationData( offset, sideA, sideB);
  }
  this->storeTangentData(calcBegin, calcEnd, tanSideA, tanSideB);
}
