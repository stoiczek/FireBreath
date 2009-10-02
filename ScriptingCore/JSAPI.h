/**********************************************************\ 
Original Author: Richard Bateman (taxilian)

Created:    Sept 24, 2009
License:    Eclipse Public License - Version 1.0
            http://www.eclipse.org/legal/epl-v10.html

Copyright 2009 Richard Bateman, Firebreath development team
\**********************************************************/

#ifndef H_FB_JSAPI
#define H_FB_JSAPI

#include "APITypes.h"
#include "AutoPtr.h"

namespace FB
{
    class JSAPI
    {
    public:
        JSAPI(void);
        virtual ~JSAPI(void);

    // Support Reference counting
    protected:
        unsigned int m_refCount;

    public:
        void addRef();
        unsigned int release();

        void invalidate();

    protected:
        // Used to fire an event to the listeners attached to this JSAPI
        virtual void FireEvent(std::string eventName, std::vector<variant>&);

    public:
        // Methods for managing event sinks (BrowserHostWrapper objects)
        virtual void attachEventSink(void *context, BrowserHostWrapper *sink);
        virtual void detachEventSink(void *context);

        // Methods for registering properties and functions to the auto-table
        virtual void registerMethod(std::string name, CallMethodPtr func);
        virtual void registerProperty(std::string name, GetPropPtr getFunc, SetPropPtr setFunc);
        virtual void registerEvent(std::string name);

        // Methods to query existance of members on the API
        virtual bool HasMethod(std::string methodName);
        virtual bool HasProperty(std::string propertyName);
        virtual bool HasPropertyIndex(int idx);
        virtual bool HasEvent(std::string eventName);

        // Methods to manage properties on the API
        virtual bool GetProperty(std::string propertyName, variant &retVal);
        virtual bool SetProperty(std::string propertyName, variant &value);
        virtual bool GetProperty(int idx, variant &retVal);
        virtual bool SetProperty(int idx, variant &value);

        // Methods to manage methods on the API
        virtual bool Invoke(std::string methodName, std::vector<variant>&, variant &retVal);

    public:
        // Example function call and read-only property; override these if desired in derived classes
        virtual bool callToString(std::vector<variant>&, variant &retVal);
        virtual bool getValid(variant &retVal);

    protected:
        MethodMap m_methodMap;
        PropertyMap m_propertyMap;
        EventMap m_eventMap;
        EventSinkMap m_sinkMap;
        
        bool m_valid;
    };

};
#endif