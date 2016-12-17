#include "..\RengaScript\include\ParametricProfile.h"
#include "ParametricProfileOutput.h"

int main (void) 
{
  script::ParametricProfile profile;
  bool isUpdateOk = profile.updateFromScript("double_tee_beam.rpfl");
  outputProfile(profile, std::cout);
  
  if(isUpdateOk)
  {
    profile.updateParameterValue("W", 6000);
    profile.updateFromScript("double_tee_beam.rpfl");
    outputProfile(profile, std::cout);
  }
	return 0;
}