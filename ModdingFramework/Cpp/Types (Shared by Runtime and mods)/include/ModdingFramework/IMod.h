#pragma once

namespace ModdingFramework {

    struct IMod {
        virtual const char*  GetName() const                                   = 0;
        virtual const char*  GetVersion() const                                = 0;
        virtual const char*  GetFolder() const                                 = 0;
        virtual const char*  GetType() const                                   = 0;
        virtual const char*  GetSource() const                                 = 0;
        virtual bool         IsLoaded() const                                  = 0;
        virtual void         SetLoaded(bool loaded)                            = 0;
        virtual void         SetData(const char* key, void* data, size_t size) = 0;
        virtual void*        GetData(const char* key)                          = 0;
        virtual size_t       GetDataSize(const char* key)                      = 0;
        virtual size_t       GetDataCount()                                    = 0;
        virtual void         ClearData()                                       = 0;
        virtual const char** GetDataKeys()                                     = 0;
        virtual bool         HasDataKey(const char* key)                       = 0;
        virtual void         RemoveDataKey(const char* key)                    = 0;
    };
}
