/////////////////////////////////////////////////////////////////////////////
// Name:        Utils.cpp
// Purpose:     tools file
// Author:      Mateusz Kosmala
// Created:     2020-03-03
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <Utils.h>
#include<boost/random/random_device.hpp>

wxString wxGetAppFile(wxString file)
{

    wxString path("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons");
    path = path + wxT("\\") + file;
    return path;

};

unsigned int Make_Random(void)
{
    boost::random::random_device gen;
    return gen();
}
