////////////////////////////////////////////////////////////////////////
//
// MPDSchema.cpp
//
// This file was generated by XMLSpy 2012r2sp1 Enterprise Edition.
//
// YOU SHOULD NOT MODIFY THIS FILE, BECAUSE IT WILL BE
// OVERWRITTEN WHEN YOU RE-RUN CODE GENERATION.
//
// Refer to the XMLSpy Documentation for further details.
// http://www.altova.com/xmlspy
//
////////////////////////////////////////////////////////////////////////


#if 0

#include "mpdschema_prefix.h"
#include <string.h>
#include "MPDSchema.h"
#include <algorithm>


#include "XercesString.h"
#include "dash_static.h"




// turn off warning: "this" used in base initializer list


namespace MPDSchema
{

	void CMPDSchema::mpd_ex_init(CMPDtype* mpd_ptr, CMPDtype_ex** mpd_ex_ptr)
	{
	    if(mpd_ptr == NULL || mpd_ex_ptr == NULL)
	    {
	        MPD_PARSER_DBG(("no mpd ptr \n"));

			return;
	    }

		*mpd_ptr = new CMPDtype_ex(mpd_ptr);
	}

	
    void CMPDSchema::MPDSchema_init(std::string& mpd_path, MPDSchema::CMPDtype_ex** ptr, MPDSchema::CMPDSchema** sch_ptr )throw(all_exceptions)
    {
        if(mpd_path.length() == 0 || ptr == NULL || sch_ptr == NULL)
        {
            MPD_PARSER_DBG(("please input mpd path\n"));
            throw all_exceptions("no mpd path\n");
        }

        MPD_PARSER_DBG(("mpd path = %s\n", mpd_path.c_str()));
        try
        {
            MPDSchema::CMPDSchema doc = MPDSchema::CMPDSchema::LoadFromFile(mpd_path);
			
			if(doc.MPD.exists())
			{
            	MPDSchema::CMPDtype root = doc.MPD.first();
				
				MPD_PARSER_DBG(("mpd parser OK\n"));
	            mpd_ex_init(&root, ptr);

				if(*ptr != NULL)
				{
				    *ptr->mpd_init();
				}
				else
				{
				    MPD_PARSER_DBG(("init error\n"));
					return;
				}
				MPD_PARSER_DBG(("init ok\n"));
	            *ptr->mpd_process();
				MPD_PARSER_DBG(("process ok\n"));
			}
			else
			{
			    MPD_PARSER_DBG(("empty mpd \n"));
			}

			std::string save_file = mpd_path.append("save");
	 		(*ptr)->SaveToFile(save_file, true);
        }
        catch (CXmlException& e)
        {
            MPD_PARSER_DBG(("Error: %s\n", e.GetInfo().c_str()));
			std::string msg = std::string(e.GetInfo());
            throw all_exceptions(msg);

        }
        catch (xercesc::XMLException& e)
        {
        	char* message = xercesc::XMLString::transcode(e.getMessage());
            MPD_PARSER_DBG(("Error: %s %d %s\n", e.getSrcFile(), e.getSrcLine(), message));
            std::string msg = std::string(e.getSrcFile());
            msg.append(message);
			xercesc::XMLString::release(&message);
            throw all_exceptions(msg);
        }
        catch (xercesc::DOMException& e)
        {
            MPD_PARSER_DBG(("Error %d %s\n", e.code, e.msg));
            throw all_exceptions("DOMException");
        }
        catch (altova::Exception& exception)
        {
            MPD_PARSER_DBG(("Error: %s\n",exception.message().c_str()));
            throw all_exceptions("Exception");
        }
        catch (altova::Error& exception)
        {
            MPD_PARSER_DBG(("Error: %s\n",exception.message().c_str()));
            throw all_exceptions("Error");
        }
        catch (std::exception& e)
        {
            MPD_PARSER_DBG(("Error: %s\n",e.what()));
            throw all_exceptions("exception");
        }
        catch (...)
        {
            MPD_PARSER_DBG(("unknow error\n"));
            throw all_exceptions("unknow error");
        }
        
    }
}

#endif