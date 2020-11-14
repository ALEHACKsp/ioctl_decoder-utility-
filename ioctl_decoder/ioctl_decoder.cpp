#include <windows.h>
#include <iostream>
#include <sstream>

std::string devices[] = { 
"FILE_DEVICE_BEEP", "FILE_DEVICE_CD_ROM", "FILE_DEVICE_CD_ROM_FILE_SYSTEM", "FILE_DEVICE_CONTROLLER", "FILE_DEVICE_DATALINK", "FILE_DEVICE_DFS", "FILE_DEVICE_DISK", "FILE_DEVICE_DISK_FILE_SYSTEM",
"FILE_DEVICE_FILE_SYSTEM", "FILE_DEVICE_INPORT_PORT", "FILE_DEVICE_KEYBOARD", "FILE_DEVICE_MAILSLOT", "FILE_DEVICE_MIDI_IN", "FILE_DEVICE_MIDI_OUT", "FILE_DEVICE_MOUSE", "FILE_DEVICE_MULTI_UNC_PROVIDER", "FILE_DEVICE_NAMED_PIPE",
"FILE_DEVICE_NETWORK", "FILE_DEVICE_NETWORK_BROWSER", "FILE_DEVICE_NETWORK_FILE_SYSTEM", "FILE_DEVICE_NULL", "FILE_DEVICE_PARALLEL_PORT", "FILE_DEVICE_PHYSICAL_NETCARD", "FILE_DEVICE_PRINTER", "FILE_DEVICE_SCANNER"
"FILE_DEVICE_SERIAL_MOUSE_PORT", "FILE_DEVICE_SERIAL_PORT", "FILE_DEVICE_SCREEN", "FILE_DEVICE_SOUND", "FILE_DEVICE_STREAMS", "FILE_DEVICE_TAPE", "FILE_DEVICE_TAPE_FILE_SYSTEM", "FILE_DEVICE_TRANSPORT", "FILE_DEVICE_UNKNOWN",
"FILE_DEVICE_VIDEO", "FILE_DEVICE_VIRTUAL_DISK", "FILE_DEVICE_WAVE_IN", "FILE_DEVICE_WAVE_OUT", "FILE_DEVICE_8042_PORT", "FILE_DEVICE_NETWORK_REDIRECTOR", "FILE_DEVICE_BATTERY", "FILE_DEVICE_BUS_EXTENDER", "FILE_DEVICE_MODEM",
"FILE_DEVICE_VDM", "FILE_DEVICE_MASS_STORAGE", "FILE_DEVICE_SMB", "FILE_DEVICE_KS", "FILE_DEVICE_CHANGER", "FILE_DEVICE_SMARTCARD", "FILE_DEVICE_ACPI", "FILE_DEVICE_DVD", "FILE_DEVICE_FULLSCREEN_VIDEO", "FILE_DEVICE_DFS_FILE_SYSTEM", "FILE_DEVICE_DFS_VOLUME",
"FILE_DEVICE_SERENUM", "FILE_DEVICE_TERMSRV", "FILE_DEVICE_KSEC", "FILE_DEVICE_FIPS", "FILE_DEVICE_INFINIBAND", "FILE_DEVICE_VMBUS", "FILE_DEVICE_CRYPT_PROVIDER", "FILE_DEVICE_WPD", "FILE_DEVICE_BLUETOOTH", "FILE_DEVICE_MT_COMPOSITE"
"FILE_DEVICE_MT_TRANSPORT", "FILE_DEVICE_BIOMETRIC", "FILE_DEVICE_PMI", "FILE_DEVICE_EHSTOR", "FILE_DEVICE_DEVAPI", "FILE_DEVICE_GPIO", "FILE_DEVICE_USBEX", "FILE_DEVICE_CONSOLE", "FILE_DEVICE_NFP", "FILE_DEVICE_SYSENV", "FILE_DEVICE_VIRTUAL_BLOCK",
"FILE_DEVICE_POINT_OF_SERVICE", "FILE_DEVICE_STORAGE_REPLICATION", "FILE_DEVICE_TRUST_ENV", "FILE_DEVICE_UCM", "FILE_DEVICE_UCMTCPCI", "FILE_DEVICE_PERSISTENT_MEMORY", "FILE_DEVICE_NVDIMM", "FILE_DEVICE_HOLOGRAPHIC", "FILE_DEVICE_SDFXHCI", "FILE_DEVICE_UCMUCSI"
};

std::string inttohexstr(int a)
{
    std::stringstream stream;
    stream << std::hex << a;
    return std::string("0x" + stream.str());
}

int main()
{
    int ioctlin = 0;
    std::string in = "";
    std::string device = "";
    std::string function = "";
    std::string access = "";
    std::string method = "";

    std::cout << "[?] IOCTL TO DECODE: ";
    std::cin >> in;

    try
    {
        ioctlin = std::stoul(in.c_str(), 0, 16);
    }
    catch (...)
    {
        std::cout << "\n\n[-] INVALID IOCTL VALUE!\n[+] Exiting In 5 Seconds!" << std::endl;
        Sleep(5000);
        exit(1);
    }

    int deviceval = (ioctlin >> 16) & 0xFFF;
    int funcval = (ioctlin >> 2) & 0xFFF;
    int accessval = (ioctlin >> 14) & 3;
    int methodval = ioctlin & 3;

    if ((deviceval <= 82) && deviceval != 0)
        device = devices[deviceval];
    else
        device = inttohexstr(deviceval);

    function = inttohexstr(funcval);

    //might be slightly wrong idk
    switch (accessval)
    {
    case 0:
        access = "FILE_ANY_ACCESS";
        break;
    case 1:
        access = "FILE_READ_ACCESS";
        break;
    case 2:
        access = "FILE_WRITE_ACCESS";
        break;
    case 3:
        access = "FILE_READ_ACCESS | FILE_WRITE_ACCESS";
        break;
    default:
        access = "FILE_DEVICE_UNKNOWN";
        break;
    }

    switch (methodval)
    {
    case 0:
        method = "METHOD_BUFFERED";
        break;
    case 1:
        method = "METHOD_IN_DIRECT";
        break;
    case 2:
        method = "METHOD_OUT_DIRECT";
        break;
    case 3:
        method = "METHOD_NEITHER";
        break;
    }
 
    std::cout << "\n#define ioctl_out     CTL_CODE(" << device << ", " << function << ", " << method << ", " << access << ")\n" << std::endl;

    std::cout << "[+] Exiting In 20 Seconds!" << std::endl;

    Sleep(20000);
    exit(0);
}