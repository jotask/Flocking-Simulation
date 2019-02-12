#include "light.hpp"

#include "utils.hpp"

namespace aiko
{

    Light::Light()
        : m_transform()
        , m_lightId(0)
        , m_radius(50)
        , m_fov(90)
        , m_color({ 1.0f, 0.8f, 0.7f })
    {
        m_transform.m_position = { 0, 15, 10 };
        m_transform.m_rotation = { -60, 0, 0 };
    }

    Transform & Light::getTranform()
    {
        return m_transform;
    }

    void Light::randomise()
    {
        auto randomv = utils::getRandomVector();

        m_transform.m_position += randomv;

    }

    Light::Color& Light::getColor()
    {
        return m_color;
    }

    void Light::createLight(const H3DRes res)
    {
        // Add light source
        m_lightId = h3dAddLightNode(H3DRootNode, "Light1", res, "LIGHTING", "SHADOWMAP");
        m_transform.applyTransform(m_lightId);

        h3dSetNodeParamF(m_lightId, H3DLight::RadiusF, 0, m_radius);
        h3dSetNodeParamF(m_lightId, H3DLight::FovF, 0, m_fov);
        h3dSetNodeParamI(m_lightId, H3DLight::ShadowMapCountI, 1);
        h3dSetNodeParamF(m_lightId, H3DLight::ShadowMapBiasF, 0, 0.01f);
        h3dSetNodeParamF(m_lightId, H3DLight::ColorF3, 0, m_color.r);
        h3dSetNodeParamF(m_lightId, H3DLight::ColorF3, 1, m_color.g);
        h3dSetNodeParamF(m_lightId, H3DLight::ColorF3, 2, m_color.b);
        h3dSetNodeParamF(m_lightId, H3DLight::ColorMultiplierF, 0, 1.0f);

    }

}
