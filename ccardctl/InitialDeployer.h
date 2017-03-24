#ifndef __INITIAL_DEPLOYER__
#define __INITIAL_DEPLOYER__
#include <syslog.h>
#include "Thread.h"
#include "DsaController.h"
namespace IrvCS
{
  /**
   * Run initial deployment in a thread.  Initial deployment occurs 
   * when the satellite powers on for the first time after launch.
   * 
   **/
  class InitialDeployer:public Thread
  {
  public:
    InitialDeployer(DsaController *controller, const std::string &initDeployFile)
      :Thread(), controller_(controller), initDeployFile_(initDeployFile)
      {
      }

    ~InitialDeployer()
      {
      }

    void *run()
      {
        syslog(LOG_INFO, "Performing Initial Deployment Operation");
        IrvCS::InitialDeployOp deployOp(controller_);

        OpStatus status=deployOp.execute();

        if ( StatOk == status )
        {
          syslog(LOG_INFO, "DSA Release/Deploy Operation Successful");
        } else if (StatTimeOut == status)
        {
          syslog(LOG_WARNING, "DSA Release/Deploy Operation Did not complete");
        } else
        {
          syslog(LOG_ERR, "DSA Release/Deploy Operation Errored with status %d", status);
        }
          
        // create the deploy file
        std::ofstream ofs(initDeployFile_.c_str(), std::ios::out);
        ofs<<"1";
        if (ofs.fail())
        {
          syslog(LOG_ERR, "Unable to create %s:  %s (%d)", initDeployFile_.c_str(),
                 strerror(errno), errno);
        }

        delete this;
      }

  private:
    DsaController *controller_;
    const std::string &initDeployFile_;
  };
}
#endif
