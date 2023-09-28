#include "three-gpp-indoorFactory-propagation-loss-model.h"
#include "ns3/double.h"
#include "ns3/log.h"
#include "ns3/string.h"


namespace ns3 {

NS_LOG_COMPONENT_DEFINE("ThreeGppIndoorFactoryPropagationLossModel");

//--------------------------------------------------------------------------------//

NS_OBJECT_ENSURE_REGISTERED(ThreeGppIndoorFactoryPropagationLossModel);

TypeId
ThreeGppIndoorFactoryPropagationLossModel::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::ThreeGppIndoorFactoryPropagationLossModel")
        .SetParent<ThreeGppPropagationLossModel> ()
        .SetGroupName("Propagation")
        .AddConstructor <ThreeGppIndoorFactoryPropagationLossModel> ()
    ;
    return tid;
}
ThreeGppIndoorFactoryPropagationLossModel::ThreeGppIndoorFactoryPropagationLossModel()
    : ThreeGppPropagationLossModel()
{
    NS_LOG_FUNCTION (this);

    //Set a default channel condition model
    m_channelConditionModel = CreateObject<ThreeGppIndoorFactoryPropagationLossModel> ();
}

ThreeGppIndoorFactoryPropagationLossModel::~ThreeGppIndoorFactoryPropagationLossModel ()
{
    NS_LOG_FUNCTION(this);
}
//LOS function definition
double
ThreeGppIndoorFactoryPropagationLossModel::GetLossLos([[maybe_unused]] double distance2D, 
                                                      [[maybe_unused]] double distance3D, 
                                                      [[maybe_unused]] double hUt, 
                                                      [[maybe_unused]] double hBs) const
{
    NS_LOG_FUNCTION(this);
    //check if the distance is outside the validity range
    if (distance3D < 1.0 || distance3D > 600)
        {
            NS_LOG_WARN("The 3D distance is oustide the validity range, the pathloss value may not be accurate");
        }
    //Compute the pathloss for InF (3GPP TR38.901, Table 7.4.1-1:Pathloss models)
    double loss = 31.84 +21.5 * log10(distance3D)+19.0 * log10(m_frequency/1e9);

    NS_LOG_DEBUG ("Loss " << loss);

    return loss;
}                     
//NLOS function definition
double
ThreeGppIndoorFactoryPropagationLossModel::GetLossNlos(double distance2D, double distance3D,double hUt, double hBs) const
{
    NS_LOG_FUNCTION (this);
    /*Here we implement for inF-DH: sparse clutter,low BS
    we assume same distance range*/
    if (distance3D < 1.0 || distance3D > 600)
        {
        NS_LOG_WARN("The 3D distance is oustide the validity range, the pathloss value may not be accurate");
        }
    //Compute the pathloss
    double pNlos = 33.63 + 21.9 * log10(distance3D) + 20 * log10(m_frequency);
    double loss = std::max(GetLossLos(distance2D, distance3D, hUt, hBs), pNlos);

    NS_LOG_DEBUG("Loss " << loss);

    return loss;
}
//Shadowing
double
ThreeGppIndoorFactoryPropagationLossModel::GetShadowingStd([[maybe_unused]] Ptr<MobilityModel> a, 
                                                           [[maybe_unused]] Ptr<MobilityModel> b, 
                                                           ChannelCondition::LosConditionValue cond) const
{
    NS_LOG_FUNCTION (this);
    double shadowingStd;

    if (cond == ChannelCondition::LosConditionValue::LOS)
        {
            shadowingStd = 10.0;
        }
    else if (cond == ChannelCondition::LosConditionValue::NLOS)
        {
            shadowingStd = 10.0;
        }
    else
        {
            NS_FATAL_ERROR ("Unknown channel condition");
        }
    
    return shadowingStd;
}
//Shadowing correlation distance
double
ThreeGppIndoorFactoryPropagationLossModel::GetShadowingCorrelationDistance(ChannelCondition::LosConditionValue cond) const
{
    NS_LOG_FUNCTION(this);

    //3GPP TR 38.901, Table 7.5-6
    double correlationDistance;

    if (cond == ChannelCondition::LosConditionValue::LOS)
        {
            correlationDistance=10;
        }
    else  if (cond == ChannelCondition::LosConditionValue::NLOS)
        {
            correlationDistance = 10;
        }
    else
        {
        NS_FATAL_ERROR ("Unknown channel condition");
        }

  return correlationDistance;      
}

}//namespace ns3