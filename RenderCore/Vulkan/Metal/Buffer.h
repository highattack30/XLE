// Copyright 2015 XLGAMES Inc.
//
// Distributed under the MIT License (See
// accompanying file "LICENSE" or the website
// http://www.opensource.org/licenses/mit-license.php)

#pragma once

#include "VulkanCore.h"
#include "IncludeVulkan.h"
#include "../../BufferUploads/IBufferUploads.h"
#include "../../../Core/Prefix.h"

namespace RenderCore { namespace Metal_Vulkan
{
    class ObjectFactory;
    class DeviceContext;

    class Buffer
    {
    public:
        using Desc = BufferUploads::BufferDesc;

        Buffer(
            const ObjectFactory& factory, const Desc& desc,
            const void* initData = nullptr, size_t initDataSize = 0);
        Buffer();

        void    Update(DeviceContext& context, const void* data, size_t byteCount);

        typedef VkBuffer    UnderlyingType;
		UnderlyingType		GetUnderlying() const { return _underlying.get(); }
        bool                IsGood() const { return _underlying != nullptr; }
    protected:
        VulkanSharedPtr<VkBuffer> _underlying;
        VulkanSharedPtr<VkDeviceMemory> _mem;
    };

        ////////////////////////////////////////////////////////////////////////////////////////////////

    class VertexBuffer : public Buffer
    {
    public:
		VertexBuffer();
        VertexBuffer(const void* data, size_t byteCount);
        VertexBuffer(const ObjectFactory& factory, const void* data, size_t byteCount);
    };

        ////////////////////////////////////////////////////////////////////////////////////////////////

    class IndexBuffer : public Buffer
    {
    public:
		IndexBuffer();
        IndexBuffer(const void* data, size_t byteCount);
        IndexBuffer(const ObjectFactory& factory, const void* data, size_t byteCount);
    };

        ////////////////////////////////////////////////////////////////////////////////////////////////

    class DeviceContext;

    class ConstantBuffer : public Buffer
    {
    public:
        ConstantBuffer(const void* data, size_t byteCount, bool immutable=true);
        ConstantBuffer(
            const ObjectFactory& factory,
            const void* data, size_t byteCount, bool immutable=true);
        ConstantBuffer();
    };

        ////////////////////////////////////////////////////////////////////////////////////////////////
    
}}
