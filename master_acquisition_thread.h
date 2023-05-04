#ifndef LIGHTLINK_VIEW_MASTER_ACQUISITION_THREAD_H
#define LIGHTLINK_VIEW_MASTER_ACQUISITION_THREAD_H

#include <eventThread.h>
#include <lightlink_master.h>

using namespace ethr;

class MasterAcquisitionThread : public EThread
{
public:
    MasterAcquisitionThread(void *masterModelPtr, const std::string &portName);
    ~MasterAcquisitionThread();
    void open();
    void search(std::vector<int> baudRates);
protected:
    virtual void task();
    virtual void onStart();
    virtual void onTerminate();
private:
    std::string mPortName;
    LLINK_Master* mMasterHandle;
    void* mMasterModelPtr;
};


#endif
