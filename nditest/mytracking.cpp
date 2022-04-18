#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "CombinedApi.h"
#include "PortHandleInfo.h"
#include "ToolData.h"
#include <ndicapi.h>
#include <cstring>

using namespace std;

void checkTheUSBPortName(string &name);

void getThePostion(const ToolData& toolData);


int main(int argc,char**argv)
{
    static CombinedApi capi = CombinedApi();

    string name_ = argv[1];

    checkTheUSBPortName(name_);
    cout<<"The usb port name is:"<<name_<<endl;

    ///connect
    if(capi.connect(name_)!=0);
        cout<<"Please check the port name\n";
    sleep(1);

    ///initialize
    capi.initialize();

    std::cout << capi.getTrackingDataTX() << std::endl;

    int portHandle = capi.portHandleRequest();

    std::vector<PortHandleInfo> portHandles = capi.portHandleSearchRequest(PortHandleSearchRequestOption::NotInit);
    for (int i = 0; i < portHandles.size(); i++)
    {
        capi.portHandleInitialize(portHandles[i].getPortHandle());
        capi.portHandleEnable(portHandles[i].getPortHandle());
    }
    portHandles = capi.portHandleSearchRequest(PortHandleSearchRequestOption::Enabled);

    ///start tracking
    capi.startTracking();

    while(true)
    {
        ///get the tool data
        std::vector<ToolData> toolData =  capi.getTrackingDataBX();

        for(auto &tl:toolData)
        {
            getThePostion(tl);
        }
    }

    ///stop tracking
    capi.stopTracking();

}

void checkTheUSBPortName(string &name)
{
    //Initialize used by old api--------This is a bug

    ndicapi* device(nullptr);
    device = ndiOpenSerial(name.c_str());

    if(device == nullptr)
    {

        const int MAX_SERIAL_PORTS = 20;
        for (int i = 0; i < MAX_SERIAL_PORTS; ++i)
        {
          name = ndiSerialDeviceName(i);
          int result = ndiSerialProbe(name.c_str(),false);
          if (result == NDI_OKAY)
          {
            break;
          }
        }

        device = ndiOpenSerial(name.c_str());
    }

}

void getThePostion(const ToolData& toolData)
{
    std::stringstream stream;
    stream << std::setprecision(toolData.PRECISION) << std::setfill('0');
    if (toolData.transform.isMissing())
    {
        stream << "Missing,,,,,,,,";
    }
    else
    {
        stream << TransformStatus::toString(toolData.transform.getErrorCode()) << ","
               << toolData.transform.q0 << "," << toolData.transform.qx << "," << toolData.transform.qy << "," << toolData.transform.qz << ","
               << toolData.transform.tx << "," << toolData.transform.ty << "," << toolData.transform.tz << "," << toolData.transform.error;
    }
    cout<<stream.str()<<endl;
}
