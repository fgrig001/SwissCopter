#include <RFController.h>



class SwissCopterExecutive{
   public:
      SwissCopterExecutive();
   private:
      uint8_t chPins[4]={2,3,4,5};

};

SwissCopterExecutive::SwissCopterExecutive()
{
     InitRFController(4,chPins);
}


