// Copyright 2015 XLGAMES Inc.
//
// Distributed under the MIT License (See
// accompanying file "LICENSE" or the website
// http://www.opensource.org/licenses/mit-license.php)

#pragma once

#include "../Metal/Shader.h"
#include "../../Assets/IntermediateResources.h"

namespace RenderCore { namespace Assets 
{
    class ShaderCacheSet;

    class OfflineCompileProcess 
        : public ::Assets::IntermediateResources::IResourceCompiler
        , public Metal::ShaderService::IShaderSource
        , public std::enable_shared_from_this<OfflineCompileProcess>
    {
    public:
        std::shared_ptr<::Assets::PendingCompileMarker> PrepareResource(
            uint64 typeCode, const ::Assets::ResChar* initializers[], unsigned initializerCount,
            const ::Assets::IntermediateResources::Store& destinationStore);

        using IPendingMarker = Metal::ShaderService::IPendingMarker;
        std::shared_ptr<IPendingMarker> CompileFromFile(
            const Metal::ShaderService::ResId& resId, 
            const ::Assets::ResChar definesTable[]) const;
            
        std::shared_ptr<IPendingMarker> CompileFromMemory(
            const char shaderInMemory[], const char entryPoint[], 
            const char shaderModel[], const ::Assets::ResChar definesTable[]) const;

        ShaderCacheSet& GetCacheSet() { return *_shaderCacheSet; }

        OfflineCompileProcess();
        ~OfflineCompileProcess();
    protected:
        std::unique_ptr<ShaderCacheSet> _shaderCacheSet;
    };
}}
