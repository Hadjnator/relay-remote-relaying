#ifndef THREE_GPP_INDOOR_FACTORY_PROPAGATION_LOSS_MODEL_H
#define THREE_GPP_INDOOR_FACTORY_PROPAGATION_LOSS_MODEL_H

#include "ns3/propagation-loss-model.h"
#include "ns3/channel-condition-model.h"
#include "three-gpp-propagation-loss-model.h"

namespace ns3 {

class ThreeGppIndoorFactoryPropagationLossModel: public ThreeGppPropagationLossModel
{
public:

static TypeId GetTypeId (void); //Get the Type Id and return the object TypeId

//Constructor
ThreeGppIndoorFactoryPropagationLossModel();

//Destructor
virtual ~ThreeGppIndoorFactoryPropagationLossModel() override;

//Copy constructor: Defined and unimplemented to avoid misuse
ThreeGppIndoorFactoryPropagationLossModel (const ThreeGppIndoorFactoryPropagationLossModel &) = delete;

//Copy constructor, defined and unimplemented to avoid misuse, return the ThreeGppIndoorFactoryPropagationLossModel
ThreeGppIndoorFactoryPropagationLossModel & operator = (const ThreeGppIndoorFactoryPropagationLossModel);

private:
 /**
   * \brief Computes the pathloss between a and b considering that the line of
   *        sight is not obstructed. -->LOS case
   * \param distance2D the 2D distance between tx and rx in meters
   * \param distance3D the 3D distance between tx and rx in meters
   * \param hUt the height of the UT in meters
   * \param hBs the height of the BS in meters
   * \return pathloss value in dB
   */
  virtual double GetLossLos(double distance2D, double distance3D, double hUt, double hBs) const override;

   /**
   * \brief Computes the pathloss between a and b considering that the line of
   *        sight is obstructed. -->NLOS case
   * \param distance2D the 2D distance between tx and rx in meters
   * \param distance3D the 3D distance between tx and rx in meters
   * \param hUt the height of the UT in meters
   * \param hBs the height of the BS in meters
   * \return pathloss value in dB
   */
    virtual double GetLossNlos(double distance2D, double distance3D, double hUt, double hBs) const override;
    
    /**
   * \brief Returns the shadow fading standard deviation
   * \param a tx mobility model
   * \param b rx mobility model
   * \param cond the LOS/NLOS channel condition
   * \return shadowing std in dB
   */
    virtual double GetShadowingStd (Ptr<MobilityModel> a, Ptr<MobilityModel> b, ChannelCondition::LosConditionValue cond) const override;

    /**
   * \brief Returns the shadow fading correlation distance
   * \param cond the LOS/NLOS channel condition
   * \return shadowing correlation distance in meters
   */
    virtual double GetShadowingCorrelationDistance (ChannelCondition::LosConditionValue cond) const override;

};

} //namespace ns3

#endif /*THREE_GPP_INDOOR_FACTORY_PROPAGATION_LOSS_MODEL_H*/