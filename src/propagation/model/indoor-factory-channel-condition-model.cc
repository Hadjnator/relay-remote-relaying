#include "indoor-factory-channel-condition-model.h"
#include "ns3/log.h"
#include "ns3/string.h"
#include "ns3/mobility-model.h"
#include "ns3/enum.h"
#include <cmath>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("IndoorFactoryChannelConditionModel");

NS_OBJECT_ENSURE_REGISTERED (IndoorFactoryChannelConditionModel);

TypeId
IndoorFactoryChannelConditionModel::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::IndoorFactoryChannelConditionModel")
        .SetParent<ThreeGppChannelConditionModel> ()
        .SetGroupName("Propagation")
        .AddConstructor<IndoorFactoryChannelConditionModel> ()
    ;
    return tid;
}
//Constuctor
IndoorFactoryChannelConditionModel::IndoorFactoryChannelConditionModel()
    : ThreeGppChannelConditionModel()
{
}

//Destructor
IndoorFactoryChannelConditionModel::~IndoorFactoryChannelConditionModel()
{
}
//LOS probability
double
IndoorFactoryChannelConditionModel::ComputePlos(Ptr <const MobilityModel> a,
                                                Ptr <const MobilityModel> b) const
{
    //Work only for BS-UE connection !!!!
    
    //Retrieve hBs and hUt
    double h_BS = std::max(a->GetPosition().z, b->GetPosition().z);
    double h_Ut = std::min(a->GetPosition().z, b->GetPosition().z);

    //compute the 2D distance between a and b
    double distance2D = Calculate2dDistance(a->GetPosition(), b->GetPosition());
    /* We consider the inF-DH scenario
    clutter size : d_clutter = 2m;  clutter density : r < 40%
    */
    double d_clutter = 2; // in [m]
    double r = 0.39; //Choosen, default value
    double k = -(d_clutter/log(1-r));
    
    //Compute the LOS probability (3GPP TR 38.901, Table 7.4.2-1: LOS probability)
    double pLos = 0.0;


}








}