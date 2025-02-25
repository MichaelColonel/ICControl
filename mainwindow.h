#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDateTime>
#include <QByteArray>
#include <QMainWindow>
#include <QSerialPort> // serial port

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>

#include <list>
#include <array>
#include <map>
#include <memory>
#include <chrono>

typedef boost::accumulators::accumulator_set< \
  double, \
  boost::accumulators::stats< \
    boost::accumulators::tag::sum, \
    boost::accumulators::tag::count, \
    boost::accumulators::tag::mean, \
    boost::accumulators::tag::moment< 2 > \
  > \
> MeanDispAccumType;

class QTimer;
class QAbstractButton;
class QDataTime;
class QProgressDialog;
class QCheckBox;

class TFile;
class TTree;
class TGraph;
class TPad;
class TCanvas;
class TH2;
class TH1;
class TH2F;
class TH1F;
class TLine;
class TGraphErrors;
class TMultiGraph;
class TF1;

#define CHANNELS_PER_CHIP 32
#define CHIPS_PER_PLANE 6
#define CHANNELS_PER_PLANE (CHANNELS_PER_CHIP * CHIPS_PER_PLANE)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum StripsOrientationType : int {
  ORIENTATION_HORIZONTAL = 0,
  ORIENTATION_VERTICAL,
  StripsOrientationType_Last
};
enum ChannelSideType : int {
  SIDE_A = 0,
  SIDE_B,
  ChannelSideType_Last
};
enum AdcResolutionType : int {
  ADC_16_BIT = 16,
  ADC_18_BIT = 18,
  ADC_20_BIT = 20,
  AdcResolutionType_Last
};

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

private slots:
  void onRootEventsTimeout();
  void onSpillTimeout();
  void onAcquisitionDeviceConnectClicked();
  void onAcquisitionDeviceDisconnectClicked();
  void onAgilentDeviceConnectClicked();
  void onAgilentDeviceDisconnectClicked();
  void acquisitionSerialPortBytesWritten(qint64);
  void acquisitionSerialPortDataReady();
  void acquisitionSerialPortError(QSerialPort::SerialPortError);
  void acquisitionDataPortBytesWritten(qint64);
  void acquisitionDataPortDataReady();
  void acquisitionDataPortError(QSerialPort::SerialPortError);
  void agilentSerialPortBytesWritten(qint64);
  void agilentSerialPortDataReady();
  void agilentSerialPortError(QSerialPort::SerialPortError);
  void onChipResetClicked();
  void onAlteraResetClicked();
  void onExternalStartClicked();
  void onAcquisitionAdcModeResolutionChanged(QAbstractButton*);
  void onCameraNumberChanged(QAbstractButton*);
  void onAcquisitionClicked();
  void onSingleShotClicked();
  void onWriteCapacitiesClicked();
  void onSetIntegrationTimeClicked();
  void onSetCapacityClicked();
  void onSetDevicesEnabled();
  void onSetSamplesClicked();
  void onSetNumberOfChipsClicked();
  void onSetFrequencyClicked();
  void onSetAmplitudeClicked();
  void onSetDutyCycleClicked();
  void onSendCommandClicked();
  void onSetOffsetClicked();
  void onAdcResolutionSetClicked();
  void onInitiateDevicesClicked();
  void onUpdateChannelGraphClicked();
  void onFitParametersClicked();
  void writeNextCommandFromInitiationList();
  void writeNextAgilentCommandFromInitiationList();
  void writeLastCommandOnceAgain();
  void onProcessSpillChannelsCountsClicked();
  void onProcessRawDataClicked();
  void onDeviceEnabledCheckBoxChecked(bool state);
  void onAllDevicesEnabledChecked(bool state);

  void onOpenRootFileClicked();
  void onProcessSelectedItemsClicked();
  void onClearSpillListClicked();
  void onPedestalsBeginClicked(int);
  void onPedestalsEndClicked(int);
  void onSignalBeginClicked(int);
  void onSignalEndClicked(int);
  void onInitiateDevicesStopClicked();
  void onInitiateDevicesFinished(int);
  void onStartIterationAcquisitionClicked();
  void onSetNextOffset();
  void onCalibrationClicked();
  void onTangentCalculationClicked();
  void onFirstConnectResponce();
  void onClearHistogramsClicked();
  void onCalibrateClicked();
private:
  int currentCameraNumber() const;
  void storeSpillData(const QDateTime& timeStamp);
  void storeCalibrationData(int offset, const std::vector<int>& sideA, const std::vector<int>& sideB);
  void storeTangentData( int calcBegin, int calcEnd, double tanSideA[CHANNELS_PER_CHIP], double tanSideB[CHANNELS_PER_CHIP]);

  bool fitSpillData(std::ofstream& ofs, const std::map< int, double >& horizProfile, const std::map< int, double >& vertProfile);
  unsigned short devicesEnabled() const;
  void saveSettings();
  void loadSettings();
  void loadICSettings();
  void loadChipChannelStripSettings();
  bool loadChipCalibration(const std::string& fileName, int position = -1);

  TCanvas* getVerticalStripsCanvas() const { return this->rootCanvas[StripsOrientationType::ORIENTATION_VERTICAL]; }
  TCanvas* getHorizontalStripsCanvas() const { return this->rootCanvas[StripsOrientationType::ORIENTATION_HORIZONTAL]; }
  TH2* getVerticalStripsHist() const { return this->hist2Strips[StripsOrientationType::ORIENTATION_VERTICAL]; }
  TH2* getHorizontalStripsHist() const { return this->hist2Strips[StripsOrientationType::ORIENTATION_HORIZONTAL]; }
  TGraphErrors* getVerticalStripsGraph() const { return this->graphStrips[StripsOrientationType::ORIENTATION_VERTICAL]; }
  TGraphErrors* getHorizontalStripsGraph() const { return this->graphStrips[StripsOrientationType::ORIENTATION_HORIZONTAL]; }
  TGraphErrors* getVerticalCalibratedStripsGraph() const { return this->graphStripsCalibrated[StripsOrientationType::ORIENTATION_VERTICAL]; }
  TGraphErrors* getHorizontalCalibratedStripsGraph() const { return this->graphStripsCalibrated[StripsOrientationType::ORIENTATION_HORIZONTAL]; }
  TMultiGraph* getVerticalStripsMultiGraph() const { return this->multiGraphStrips[StripsOrientationType::ORIENTATION_VERTICAL]; }
  TMultiGraph* getHorizontalStripsMultiGraph() const { return this->multiGraphStrips[StripsOrientationType::ORIENTATION_HORIZONTAL]; }
  TH1* getChannelHistSideA() const { return this->histChannel[ChannelSideType::SIDE_A]; }
  TH1* getChannelHistSideB() const { return this->histChannel[ChannelSideType::SIDE_B]; }
  bool checkLastCommandWrittenAndRespose();
  bool checkLastCommandWrittenAndRespose(const QByteArray&);
  void setAgilentOffset(double mV);
  void setAgilentAmplitude(double mV);
  void setAgilentDutyCycle(int percents);


  Ui::MainWindow *ui{ nullptr };
  QSerialPort* acquisitionPort{ nullptr };
  QSerialPort* acquisitionDataPort{ nullptr };
  QSerialPort* agilentPort{ nullptr };
  QTimer* timer{ nullptr }; // ROOT GUI update timer
  QByteArray acquisitionResponseBuffer;
  QByteArray acquisitionDataBuffer;

  TCanvas* rootCanvas[2]{ nullptr, nullptr }; // TCanvas
  TH2* hist2Strips[2]{ nullptr, nullptr }; // TH2 integral histograms
  TPad* hist2Pad[2]{ nullptr, nullptr };
  TGraphErrors* graphStrips[2]{ nullptr, nullptr }; // TGraph for each spill
  TGraphErrors* graphStripsCalibrated[2]{ nullptr, nullptr }; // TGraph for each spill with calibration
  TMultiGraph* multiGraphStrips[2]{ nullptr, nullptr }; // TMultiGraph for vertical and horizontal
  TPad* graphPad[2]{ nullptr, nullptr }; // TPad for spill graphs
  TPad* channelPad{ nullptr };
  TGraph* graphChannel{ nullptr };
  TCanvas* sideCanvas[2]{ nullptr, nullptr };
  TH1* histChannel[2]{ nullptr, nullptr };
  TPad* channelHistPad[2]{ nullptr, nullptr };
  TGraphErrors* graphFit[2]{ nullptr, nullptr };
  TPad* padFit[2]{ nullptr, nullptr };
  TFile* rootFile{ nullptr };
  QString rootFileName;
  std::map< int, std::array< std::vector< int >, CHANNELS_PER_CHIP > > channelsCountsA, channelsCountsB;
  std::vector< int > chipsAddresses;
  mutable QList< QByteArray > initiateDevicesCommandsList;
  mutable QList< QByteArray > agilentDeviceCommandsList;
  mutable QByteArray lastCommandWritten;
  mutable QByteArray lastAgilentCommandWritten;
  std::unique_ptr< TLine > linePedBegin;
  std::unique_ptr< TLine > linePedEnd;
  std::unique_ptr< TLine > lineSignalBegin;
  std::unique_ptr< TLine > lineSignalEnd;
  struct ChamberResponse {
    int ChipsEnabled{ -1 };
    unsigned short ChipsEnabledCode{ 0x0FFF };
    int IntegrationTimeCode{ 1 }; // Integration time code(0...15)
    int AdcMode{ 16 }; // 16-bit or 20-bit (16 or 20)
    int CapacityCode{ 7 }; // Capacity code (0...7)
    bool ExternalStartState{ false };
  } chamberResponse;
  struct ChannelInfo {
    double pedMeanA{ -1. };
    double pedMeanB{ -1. };
    double pedMom2A{ -1. };
    double pedMom2B{ -1. };
    double sigMeanA{ -1. };
    double sigMeanB{ -1. };
    double sigMom2A{ -1. };
    double sigMom2B{ -1. };
    double sigCountA{ -1. };
    double sigCountB{ -1. };
    double sigSumA{ -1. };
    double sigSumB{ -1. };
  };
  std::chrono::steady_clock::time_point timeWaitingBegin, timeWaitingEnd;
  QProgressDialog* initiationProgress{ nullptr };
  int spillNumber{ -1 };
  QTimer* spillTimeoutTimer{ nullptr };
  QTimer* initiationTimer{ nullptr };
  bool calibrationEnabled{ false };
  std::list< int > agilentOffsets;
  std::map< int, std::pair< std::vector< int >, std::vector< int > > > calibrationChannelsCounts;
  std::map< std::pair< int, int >, double > chipChannelCalibrationA;
  std::map< std::pair< int, int >, double > chipChannelCalibrationB;
  std::map< std::pair< int, int >, double > chipChannelCalibrationAmplitude;

  TCanvas* calibrationCanvas{ nullptr };
  TPad* calibrationPad{ nullptr };
  TGraph* calibrationGraph{ nullptr };
  std::array< QCheckBox*, CHIPS_PER_PLANE * 2 > CheckBox_DevicesEnabled;

  std::array< std::pair< int, int >, CHANNELS_PER_CHIP * 4 > verticalChipChannelStrips;
  std::array< std::pair< int, int >, CHANNELS_PER_PLANE > horizontalChipChannelStrips;
  double channelStepPerSideMM = 2.;
};

#endif // MAINWINDOW_H
