#include "model.h"

Model::SlaveTableModel::SlaveTableModel(LLINK_Master_Summary &summary)
{
    for(int typeIndex = 0; typeIndex < summary.nObjectTypes; typeIndex++)
    {
        LLINK_Master_TypedObjectList* typedList = summary.objectLists + typeIndex;
        mTable.emplace_back(typedList->typeName, typedList->typeSize);
        for(int objectIndex = 0; objectIndex < typedList->nObjects; objectIndex++)
        {
            LLINK_Master_Object* object = typedList->objects+objectIndex;
            (mTable.end()-1)->addObject(object->name, object->access);
        }
    }
    LLINK_Master_freeSummary(&summary);
}

std::vector<Model::SlaveTableModel::TypedList> &Model::SlaveTableModel::get()
{
    return mTable;
}

Model::SlaveModel::SlaveModel(int baudRate, int id, LLINK_Master_Summary summary) : mTable(summary)
{
    mBaudRate = baudRate;
    mId = id;
}

Model::SlaveModel::~SlaveModel()
{

}

int Model::SlaveModel::getBaudRate()
{
    return mBaudRate;
}

Model::SlaveTableModel &Model::SlaveModel::getTableModel()
{
    return mTable;
}

uint8_t Model::SlaveModel::getID()
{
    return mId;
}


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

Model::SlaveTableModel::TypedList::Object::Object(const std::string &name, LLINK_Access access, size_t typeSize)
{
    mName = name;
    mAccess = access;
    mIsValueValid = false;
    mValue.resize(typeSize);
}

const std::string &Model::SlaveTableModel::TypedList::Object::getName()
{
    return mName;
}

LLINK_Access Model::SlaveTableModel::TypedList::Object::getAccess()
{
    return mAccess;
}

const std::vector<uint8_t>& Model::SlaveTableModel::TypedList::Object::getValue()
{
    return mValue;
}

Model::SlaveTableModel::TypedList::TypedList(const std::string &typeName, const size_t &typeSize)
{
    mTypeName = typeName;
    mTypeSize = typeSize;
}

void Model::SlaveTableModel::TypedList::addObject(const std::string &name, LLINK_Access access)
{
    mObjects.emplace_back(name, access, mTypeSize);
}

std::vector<Model::SlaveTableModel::TypedList::Object> & Model::SlaveTableModel::TypedList::getObjects()
{
    return mObjects;
}

const std::string &Model::SlaveTableModel::TypedList::getTypeName()
{
    return mTypeName;
}

const size_t &Model::SlaveTableModel::TypedList::getTypeSize()
{
    return mTypeSize;
}
