// Copyright (c) Microsoft Open Technologies, Inc. All rights reserved.
// Licensed under the Apache License, Version 2.0. See License.txt in the project root for license information.

#pragma once

#include<atomic>
#include<unordered_map>
#include<functional>
#include<mutex>
#include<cpprest\json.h>

namespace signalr
{
    class callback_manager
    {
    public:
        explicit callback_manager(const web::json::value& dtor_error);
        ~callback_manager();

        callback_manager(const callback_manager&) = delete;
        callback_manager& operator=(const callback_manager&) = delete;

        int register_callback(const std::function<void(const web::json::value&)>& callback);
        bool complete_callback(int callback_id, const web::json::value& arguments);
        void clear(const web::json::value& arguments);

    private:
        std::atomic<int> m_id = 0;
        std::unordered_map<int, std::function<void(const web::json::value&)>> m_callbacks;
        std::mutex m_map_lock;
        const web::json::value m_dtor_clear_arguments;
    };
}