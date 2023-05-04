#ifndef LIGHTLINK_VIEW_MODEL_H
#define LIGHTLINK_VIEW_MODEL_H

#include <lightlink_master.h>
#include <vector>
#include <iostream>
#include <map>
#include <eventThread.h>
#include <memory>
#include "master_acquisition_thread.h"

using namespace ethr;


class Model
{
public:
    class SlaveModel
    {
    public:
        SlaveModel(int baudRate, int id, LLINK_Master_Summary summary);
        ~SlaveModel();
        int mBaudRate;
        uint8_t mId;
        LLINK_Master_Summary mSummary;
    };

    class MasterModel : public EThreadObject
    {
    public:
        enum class PortState{
            OPENED,
            OPEN_FAILED,
            CLOSED,
            CLOSE_FAILED,
        };
        MasterModel(const std::string &portName);
        ~MasterModel();
        void notifyPortState(PortState portState);
        void search(std::vector<int>& baudRates);
        const std::string& getPortName();
        void notifySlaveFound(int baudRate, int id, LLINK_Master_Summary summary);
        std::map<int, std::map<int, std::unique_ptr<SlaveModel>>>& getSlaves();
    private:
        std::unique_ptr<MasterAcquisitionThread> mAcquisitionThread;
        PortState mPortState;
        std::string mPortName;
        std::map<int, std::map<int, std::unique_ptr<SlaveModel>>> mSlaves;
    };

    Model();
    const std::vector<std::string>& getPortNames();
    void updatePortNames();
    enum class AddMasterError
    {
        NO_ERROR,
        MASTER_ALREADY_DESIGNATED,
        NO_SUCH_PORT,
    };
    AddMasterError addMaster(const std::string &portName);
    std::map<std::string, std::unique_ptr<MasterModel>>& getMasters(){return mMasters;}
private:
    std::vector<std::string> mPortNames;
    std::map<std::string, std::unique_ptr<MasterModel>> mMasters;
};


#endif
