//
// Created by Jin Kim on 2023/05/04.
//

#include "master_acquisition_thread.h"
#include "model.h"

MasterAcquisitionThread::MasterAcquisitionThread(void *masterModelPtr, const std::string &portName) : EThread(portName)
{
    mMasterModelPtr = masterModelPtr;
    mPortName = portName;
    mMasterHandle = LLINK_Master_create();
    setLoopFreq(1000);
}

MasterAcquisitionThread::~MasterAcquisitionThread()
{
    LLINK_Master_close(mMasterHandle);
    LLINK_Master_destroy(mMasterHandle);
}

void MasterAcquisitionThread::onStart()
{
    open();
}

void MasterAcquisitionThread::task()
{

}

void MasterAcquisitionThread::onTerminate()
{

}

void MasterAcquisitionThread::open()
{
    if(LLINK_Master_open(mMasterHandle, mPortName.c_str(), 115200) == LLINK_ERROR_NO_ERROR)
        ((Model::MasterModel*)mMasterModelPtr)->callQueued(&Model::MasterModel::notifyPortState, Model::MasterModel::PortState::OPENED);
    else
        ((Model::MasterModel*)mMasterModelPtr)->callQueued(&Model::MasterModel::notifyPortState, Model::MasterModel::PortState::OPEN_FAILED);
}

void MasterAcquisitionThread::search(std::vector<int> baudRates)
{
    if(! LLINK_Master_isOpen(mMasterHandle))
        return;

    for(int i=0; i<5; i++)
    {
        if(LLINK_Master_pingDevice(mMasterHandle, i, 10) == LLINK_ERROR_NO_ERROR)
        {
            std::cout<<"found device at " << i <<std::endl;
            LLINK_Master_Summary summary;
            LLINK_Master_summarizeDevice(mMasterHandle, i, &summary, 1000);
            ((Model::MasterModel*)mMasterModelPtr)->callQueued(&Model::MasterModel::notifySlaveFound, 115200, i, summary);
        }
    }
    std::cout<<"done"<<std::endl;
}
