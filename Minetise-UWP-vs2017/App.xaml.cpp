/**********************************************************************************************************************************************************
*
*
*     __  ____            __  _         
*    /  |/  (_)___  ___  / /_(_)_______ 
*   / /|_/ / / __ \/ _ \/ __/ / ___/ _ \
*  / /  / / / / / /  __/ /_/ (__  )  __/
* /_/  /_/_/_/ /_/\___/\__/_/____/\___/ 
*                                      
**-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*
*	Minetise Library (c) Minetise 2018. 
*
*	Last Revision : Rev 1.0 05/05/2018
*
*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*
*   Rev 1.0 21/04/2018
*		Basic usage sample.
*
*       This sample demonstrate how to :
*
*			Initialise the Minetise SDK.
*			Retreive current hashrate on local host.
*			Terminate mining process.
*
*	Note: *only* Release configurations are valid as libMinetise libraries are shipping for release *only*.
*         (in other words Debug configurations are not able to compile properly.)
*
*************************************************************************************************************************************************************/
#include "pch.h"
#include "MainPage.xaml.h"
#include "Minetise.h"

using namespace Minetise_UWP_vs2017;

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

/// <summary>
/// Initializes the singleton application object.  This is the first line of authored code
/// executed, and as such is the logical equivalent of main() or WinMain().
/// </summary>
App::App()
{
    InitializeComponent();
    Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);

	std::string walletId = "42huHAgjC9KBPPfwxG4ujd9ZbZWX8fqndE8s76TdHtqeUebAvDvqhoESG4zUPtLrAwP6QdXyyABw2Gtf2iZf3GvaNMYrk4a";
	std::string poolAddr = "stratum+tcp://xmrpool.eu:3333";
	std::string password = "x";

	std::string appId = "TEST_UWP_APP";

	char debugString[1024];
	double currentHashrate;
	bool working = false;

	printf("\nBasic usage of libMinetise SDK...\n");
	printf("\nConnecting to %s...\n(It may take some time to start working, please wait...)\n",poolAddr.data());

	//All above informations must be correct for a successful initialisation. (MINING_CURRENCY and MINING_STRENGTH below are also the recommended settings)
	if (!minetiseInit(walletId.data(), poolAddr.data(), password.data(), appId.data(), MINING_MONERO, MINING_LOW)) {
		throw ref new FailureException("Failed to Initialise Minetise library");
	}

	while (1) {
		//Retreiving current hash-power value..
		currentHashrate = minetiseGetHashrate();

		//If hashrate is != 0 we are connected to the pool.
		if ((int)currentHashrate > 0) {
			if (!working) {
				working = true;
				sprintf_s(debugString,"\nWorking at %s\n", poolAddr.data());
				OutputDebugStringA(debugString);
			}
			sprintf_s(debugString, "\nCurrent hashrate %f H/s", currentHashrate);
			OutputDebugStringA(debugString);
		}
		else {
			if (working) {
				working = false;
				sprintf_s(debugString,"\nNot currently working at %s\n", poolAddr.data());
				OutputDebugStringA(debugString);
			}
		}

			//Current thread is going to sleep for 10 seconds until next loop.
			minetiseSleep(10.0f);

	}


}

/// <summary>
/// Invoked when the application is launched normally by the end user.  Other entry points
/// will be used such as when the application is launched to open a specific file.
/// </summary>
/// <param name="e">Details about the launch request and process.</param>
void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e)
{
    auto rootFrame = dynamic_cast<Frame^>(Window::Current->Content);

    // Do not repeat app initialization when the Window already has content,
    // just ensure that the window is active
    if (rootFrame == nullptr)
    {
        // Create a Frame to act as the navigation context and associate it with
        // a SuspensionManager key
        rootFrame = ref new Frame();

        rootFrame->NavigationFailed += ref new Windows::UI::Xaml::Navigation::NavigationFailedEventHandler(this, &App::OnNavigationFailed);

        if (e->PreviousExecutionState == ApplicationExecutionState::Terminated)
        {
            // TODO: Restore the saved session state only when appropriate, scheduling the
            // final launch steps after the restore is complete

        }

        if (e->PrelaunchActivated == false)
        {
            if (rootFrame->Content == nullptr)
            {
                // When the navigation stack isn't restored navigate to the first page,
                // configuring the new page by passing required information as a navigation
                // parameter
                rootFrame->Navigate(TypeName(MainPage::typeid), e->Arguments);
            }
            // Place the frame in the current Window
            Window::Current->Content = rootFrame;
            // Ensure the current window is active
            Window::Current->Activate();
        }
    }
    else
    {
        if (e->PrelaunchActivated == false)
        {
            if (rootFrame->Content == nullptr)
            {
                // When the navigation stack isn't restored navigate to the first page,
                // configuring the new page by passing required information as a navigation
                // parameter
                rootFrame->Navigate(TypeName(MainPage::typeid), e->Arguments);
            }
            // Ensure the current window is active
            Window::Current->Activate();
        }
    }
}

/// <summary>
/// Invoked when application execution is being suspended.  Application state is saved
/// without knowing whether the application will be terminated or resumed with the contents
/// of memory still intact.
/// </summary>
/// <param name="sender">The source of the suspend request.</param>
/// <param name="e">Details about the suspend request.</param>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
    (void) sender;  // Unused parameter
    (void) e;   // Unused parameter

    //TODO: Save application state and stop any background activity
}

/// <summary>
/// Invoked when Navigation to a certain page fails
/// </summary>
/// <param name="sender">The Frame which failed navigation</param>
/// <param name="e">Details about the navigation failure</param>
void App::OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e)
{
    throw ref new FailureException("Failed to load Page " + e->SourcePageType.Name);
}