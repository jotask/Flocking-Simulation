#include "light.hpp"

namespace aiko
{

    Light::Light()
        : m_transform()
        , m_lightId(0)
    {
        m_transform.m_position = { 0, 15, 10 };
        m_transform.m_rotation = { -60, 0, 0 };
    }

    Transform & Light::getTranform()
    {
        return m_transform;
    }

    void Light::createLight(const H3DRes res)
    {
        // // Add light source
        m_lightId = h3dAddLightNode(H3DRootNode, "Light1", res, "LIGHTING", "SHADOWMAP");
        m_transform.applyTransform(m_lightId);

        //  todo provide member variables for this
        
        h3dSetNodeParamF(m_lightId, H3DLight::RadiusF, 0, 30);
        h3dSetNodeParamF(m_lightId, H3DLight::FovF, 0, 90);
        h3dSetNodeParamI(m_lightId, H3DLight::ShadowMapCountI, 1);
        h3dSetNodeParamF(m_lightId, H3DLight::ShadowMapBiasF, 0, 0.01f);
        h3dSetNodeParamF(m_lightId, H3DLight::ColorF3, 0, 1.0f);
        h3dSetNodeParamF(m_lightId, H3DLight::ColorF3, 1, 0.8f);
        h3dSetNodeParamF(m_lightId, H3DLight::ColorF3, 2, 0.7f);
        h3dSetNodeParamF(m_lightId, H3DLight::ColorMultiplierF, 0, 1.0f);

    }

}
