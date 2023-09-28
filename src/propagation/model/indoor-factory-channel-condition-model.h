#ifndef INDOOR_FACTORY_CHANNEL_CONDITION_MODEL_H
#define INDOOR_FACTORY_CHANNEL_CONDITION_MODEL_H

#include "ns3/channel-condition-model.h"

namespace ns3 {

class MobilityModel;

class IndoorFactoryChannelConditionModel: public ThreeGppChannelConditionModel
{
public:

static TypeId GetTypeId (void);

//Constructor for the IndoorFactoryChannelConditionModel class
IndoorFactoryChannelConditionModel();

//Destructor for the IndoorFactoryChannelConditionModel class
virtual ~IndoorFactoryChannelConditionModel() override;

private:
/**
   * Compute the LOS probability as specified in Table 7.4.2-1 of 3GPP TR 38.901
   * for the RMa scenario.
   *
   * \param a tx mobility model
   * \param b rx mobility model
   * \return the LOS probability
   */
  virtual double ComputePlos (Ptr<const MobilityModel> a, Ptr<const MobilityModel> b) const override;
};

}

#endif /*INDOOR_FACTORY_CHANNEL_CONDITION_MODEL*/