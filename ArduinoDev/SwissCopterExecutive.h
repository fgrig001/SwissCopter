#include "RFController.h"

class SwissCopterExecutive{
   public:
      SwissCopterExecutive();
      ~SwissCopterExecutive();
   private:
      RFController Controller;
      uint8_t chPins[4]={2,3,4,5};

}

SwissCopterExecutive::SwissCopterExecutive():
   Controller(4,&chPins)
{

}
