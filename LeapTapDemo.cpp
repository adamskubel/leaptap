#include <Leap.h>

using namespace Leap;

struct TapDetector : public Listener {

	Frame lastFrame;
	void onPolledFrame(const Controller & controller)
	{
		int MaxHistory = 100;
		for (int i=1;i < MaxHistory; i++)
			{
				Frame frame = controller.frame(i-1);
				Frame previousFrame = controller.frame(i);

				if (!previousFrame.isValid())
					break;

		for (int p = 0; p < frame.pointables().count();p++)
		{
			Pointable pN = frame.pointables()[p];
			Pointable pN_prev = previousFrame.pointable(pN.id());

			if (!pN_prev.isValid())
			continue; //Pointable has only been around for one frame

			//Look for the transition from inside to outside of the touchzone
			if (pN_prev.touchDistance() <= 0 && pN.touchDistance() > 0)
			{
				 printf("App Thread: Pointable %d tapped\n",pN.id());
				}
			}

			//We reached the frame processed last time
			if (previousFrame.id() == lastFrame.id())
				break;

		}
		lastFrame = controller.frame();
	}

	void onFrame(const Controller & controller)
	{
		Frame currentFrame = controller.frame();
		Frame lastFrame = controller.frame(1);

		if (!lastFrame.isValid()) 
		return; //Only one frame so far - do nothing


		for (int p = 0; p < currentFrame.pointables().count();p++)
		{
			Pointable pN = currentFrame.pointables()[p];
			Pointable pN_prev = lastFrame.pointable(pN.id());

			if (!pN_prev.isValid())
				continue; //Pointable has only been around for one frame

			//Look for the transition from inside to outside of the touchzone
			if (pN_prev.touchDistance() <= 0 && pN.touchDistance() > 0)
			{
				printf("Leap Thread: Pointable %d tapped\n",pN.id());
			}
		}
	}
}


int main()
{
	Controller controller;
	TapDetector tapDetector;

	while (true)
	{
		tapDetector.onPolledFrame(controller);

		//Other application logic

		//Rendering 
	}
}