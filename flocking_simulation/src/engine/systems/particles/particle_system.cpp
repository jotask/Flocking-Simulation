#include "engine/systems/particles/particle_system.hpp"

#include "engine/modules/module_connector.hpp"
#include "engine/systems/system_connector.hpp"
#include "engine/shared/utils.hpp"
#include "engine/systems/entity/planet.hpp"
#include "engine/systems/entity/entity_system.hpp"
#include "engine/systems/assets/asset_system.hpp"

// #define SPEHERE_ON_CENTER_WORLD

namespace aiko
{


    void normalize(float &x, float &y, float &z)
    {
        // Calculate length
        float length = sqrtf(x * x + y * y + z * z);
        float invLength = 1.0f / length;

        x *= invLength;
        y *= invLength;
        z *= invLength;
    }

    ParticleSystem::ParticleSystem()
        :   System()
    {
        _animTime = 0;
    }

    void ParticleSystem::connect(SystemConnector& systemConnectar, ModuleConnector& moduleConnector)
    {
        m_assetSystem = systemConnectar.findSystem<AssetsSystem>();
    }

    void ParticleSystem::init()
    {

        if (!h3dGetDeviceCapabilities(H3DDeviceCapabilities::GeometryShaders) &&
            !h3dGetDeviceCapabilities(H3DDeviceCapabilities::ComputeShaders))
            return;

        // 1. Add resources

        // Shader for deferred shading
        H3DRes lightMatRes = h3dAddResource(H3DResTypes::Material, "materials/light.material.xml", 0);

        // Shader that contains geometry and compute shaders for particles
        _computeMatRes = h3dAddResource(H3DResTypes::Material, "materials/compute.material.xml", 0);
        H3DRes computeDrawMatRes = h3dAddResource(H3DResTypes::Material, "materials/computeDraw.material.xml", 0);

        // 2. Specify compute buffer parameters

        // Below is the code that manually sets the parameters of the compute buffer (recommended way)
        // You can also load buffer parameters from file, although it may be slower due to parsing overhead

        // Create compute buffer 
        // If you wish to load compute buffer data from file then exclude NoQuery flag
        H3DRes compBuf = h3dAddResource(H3DResTypes::ComputeBuffer, "CompBuf", H3DResFlags::NoQuery);

        // Generate random position data for particles
        size_t particlesCount = 1000000;
        ParticleData* compData = static_cast<ParticleData*>(malloc(sizeof(ParticleData) * particlesCount));
        if (!compData)
        {
            std::cout << "Out of memory when allocating particle data" << std::endl;
            return;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis3(-3, 3);
        std::uniform_real_distribution<> dis10(-10, 10);
        std::uniform_real_distribution<> dis30(-30, 30);
        std::uniform_real_distribution<> dis100(0, 100);

        float angle = 0;
        for (size_t i = 0; i < particlesCount; ++i)
        {
            compData[i].position[0] = (float)dis10(gen);
            compData[i].position[1] = (float)dis3(gen);
            compData[i].position[2] = (float)dis30(gen);
            compData[i].position[3] = 1.0f; // padding

            normalize(compData[i].position[0], compData[i].position[1], compData[i].position[2]);
            compData[i].position[0] *= (float)dis100(gen);
            compData[i].position[1] *= (float)dis100(gen);
            compData[i].position[2] *= (float)dis100(gen);

            angle = -(float)atan2f(compData[i].position[0], compData[i].position[2]);

            compData[i].velocity[0] = cosf(angle);
            compData[i].velocity[1] = 0.f;
            compData[i].velocity[2] = sinf(angle) * 5.f;
            compData[i].velocity[3] = 0.0f; // padding
        }

        // Set size of the compute buffer
        h3dSetResParamI(compBuf, H3DComputeBufRes::ComputeBufElem, 0, H3DComputeBufRes::CompBufDataSizeI, (int)particlesCount * sizeof(ParticleData));

        // Mark that compute buffer will be used for rendering as a vertex buffer
        h3dSetResParamI(compBuf, H3DComputeBufRes::ComputeBufElem, 0, H3DComputeBufRes::CompBufDrawableI, 1);

        // Set vertex binding parameters.
        // Name - name of the parameter. Used for binding parameter to shader variable.
        // Size - number of components (4 floats for particle position, so 4), 
        // Offset - number of bytes. For second parameter it is 16, because the first parameter had 4 floats (16 bytes)
        h3dSetResParamStr(compBuf, H3DComputeBufRes::DrawParamsElem, 0, H3DComputeBufRes::DrawParamsNameStr, "partPosition");
        h3dSetResParamI(compBuf, H3DComputeBufRes::DrawParamsElem, 0, H3DComputeBufRes::DrawParamsSizeI, /*3*/ 4);
        h3dSetResParamI(compBuf, H3DComputeBufRes::DrawParamsElem, 0, H3DComputeBufRes::DrawParamsOffsetI, 0);
        h3dSetResParamStr(compBuf, H3DComputeBufRes::DrawParamsElem, 1, H3DComputeBufRes::DrawParamsNameStr, "partVelocity");
        h3dSetResParamI(compBuf, H3DComputeBufRes::DrawParamsElem, 1, H3DComputeBufRes::DrawParamsSizeI, /*3*/ 4);
        h3dSetResParamI(compBuf, H3DComputeBufRes::DrawParamsElem, 1, H3DComputeBufRes::DrawParamsOffsetI, /*12*/ 16);

        // Fill compute buffer with generated data
        void *data = h3dMapResStream(compBuf, H3DComputeBufRes::ComputeBufElem, 0, 0, false, true);
        memcpy(data, compData, particlesCount * sizeof(ParticleData));
        h3dUnmapResStream(compBuf);
        free(compData);

        // 3. Load resources

        // if (!h3dutLoadResourcesFromDisk(getResourcePath()))
        // {
        //     h3dutDumpMessages();
        //     return false;
        // }

        // 4. Add scene nodes

        // Add camera
        // _cam = h3dAddCameraNode(H3DRootNode, "Camera", getPipelineRes());

        // In order to draw the results of compute buffer we need a compute node
        _compNode = h3dAddComputeNode(H3DRootNode, "Vortex", computeDrawMatRes, compBuf, 2, (int)particlesCount);

        // Set node AABB size because currently there is no way to do it otherwise
        h3dSetNodeParamF(_compNode, H3DComputeNode::AABBMinF, 0, -100.0f); // x
        h3dSetNodeParamF(_compNode, H3DComputeNode::AABBMinF, 1, -100.0f); // y
        h3dSetNodeParamF(_compNode, H3DComputeNode::AABBMinF, 2, -100.0f); // z
        h3dSetNodeParamF(_compNode, H3DComputeNode::AABBMaxF, 0, 100.0f); // x
        h3dSetNodeParamF(_compNode, H3DComputeNode::AABBMaxF, 1, 100.0f); // y
        h3dSetNodeParamF(_compNode, H3DComputeNode::AABBMaxF, 2, 100.0f); // z

                                                                          // If you wish, you can change the number of drawn elements and drawing type on the fly
                                                                          //	h3dSetNodeParamI( _compNode, H3DComputeNode::DrawTypeI, 2 ); 	// Set preferred draw type (for this example we draw with points - 2)
                                                                          //	h3dSetNodeParamI( _compNode, H3DComputeNode::ElementsCountI, ( int ) particlesCount ); 	// Set number of elements to draw (for this example we draw 1000000 points)

                                                                          // Set material uniforms that will not be changed during runtime
        h3dSetMaterialUniform(_computeMatRes, "totalParticles", (float)particlesCount, 0, 0, 0);

        // Calculate number of groups for compute shader
        size_t numGroups = (particlesCount % 1024 != 0) ? ((particlesCount / 1024) + 1) : (particlesCount / 1024);
        double root = pow((double)numGroups, (double)(1.0 / 2.0));
        root = ceil(root);
        _computeGroupX = _computeGroupY = (unsigned int)root;

    }

    bool ParticleSystem::initResources()
    {
        return true;
    }

    void ParticleSystem::update(const TimeStep & step)
    {

        const float frame_time = 1.0f / step.getFPS();

        // Calculate animation time in seconds
        _animTime += frame_time;

        // Set animation time
        h3dSetMaterialUniform(_computeMatRes, "deltaTime", 1.0f / H3D_FPS_REFERENCE, 0, 0, 0);

        // Set attractor point
        float angle = (float)_animTime * 0.5f;

        float attractorX = cosf(angle);
        float attractorY = cosf(angle) * sinf(angle);
        float attractorZ = sinf(angle);

        h3dSetMaterialUniform(_computeMatRes, "attractor", attractorX * 2, attractorY * 2, attractorZ * 2, 0);

        // Perform computing
        h3dCompute(_computeMatRes, "COMPUTE", _computeGroupX /*1024*/, _computeGroupY /*1*/, 1);
    }

}

