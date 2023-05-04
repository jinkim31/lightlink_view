#include "model.h"

Model::MasterModel::MasterModel(const std::string &portName)
{
    mPortName = portName;
    mAcquisitionThread = std::make_unique<MasterAcquisitionThread>(this, portName);
    mAcquisitionThread->start();
    mPortState = PortState::CLOSED;
}

Model::MasterModel::~MasterModel()
{
    mAcquisitionThread->stop();
}

void Model::MasterModel::notifyPortState(Model::MasterModel::PortState portState)
{
    switch(mPortState)
    {
    case PortState::OPENED:
    {
        switch(portState)
        {
        case PortState::CLOSED:
            mPortState = PortState::CLOSED;
            break;
        case PortState::CLOSE_FAILED:
            std::cerr<<"close failed"<<std::endl;
            break;
        default:
            std::cerr<<"invalid port state on opened"<<std::endl;
        }
        break;
    }
    case PortState::CLOSED:
    {

        switch(portState)
        {
        case PortState::OPENED:
            mPortState = PortState::OPENED;
            break;
        case PortState::OPEN_FAILED:
            std::cerr<<"opend failed"<<std::endl;
            break;
        default:
            std::cerr<<"invalid port state on closed"<<std::endl;
        }
        break;
    }
    default:
        std::cerr<<"invalid master model port state"<<std::endl;
    }
}

void Model::MasterModel::search(std::vector<int> &baudRates)
{
    mAcquisitionThread->callQueued(&MasterAcquisitionThread::search, baudRates);
}

const std::string &Model::MasterModel::getPortName()
{
    return mPortName;
}

void Model::MasterModel::notifySlaveFound(int baudRate, int id, LLINK_Master_Summary summary)
{
    mSlaves[baudRate][id] = std::make_unique<SlaveModel>(baudRate, id, summary);
    LLINK_Master_printSummary(&summary);
}

std::map<int, std::map<int, std::unique_ptr<Model::SlaveModel>>> &Model::MasterModel::getSlaves()
{
    return mSlaves;
}

Model::SlaveModel::SlaveModel(int baudRate, int id, LLINK_Master_Summary summary)
{
    mBaudRate = baudRate;
    mId = id;
    mSummary = summary;
}

Model::SlaveModel::~SlaveModel()
{
    LLINK_Master_freeSummary(&mSummary);
}

Model::Model()
{
    updatePortNames();
}

const std::vector<std::string> &Model::getPortNames()
{
    return mPortNames;
}

void Model::updatePortNames()
{
    mPortNames.clear();
    size_t nPorts;
    char** portNames = LLINK_Master_getPortNames(&nPorts);
    for(int i=0; i<nPorts; i++)
    {
        mPortNames.emplace_back(portNames[i]);
    }
    LLINK_Master_freePortNames(portNames);
}

Model::AddMasterError Model::addMaster(const std::string &portName)
{
    if(mMasters.contains(portName))
        return AddMasterError::MASTER_ALREADY_DESIGNATED;
    mMasters.insert({portName, std::make_unique<MasterModel>(portName)});
    return Model::AddMasterError::NO_ERROR;
}