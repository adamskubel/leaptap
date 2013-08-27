#include <Leap.h>

using namespace Leap;

struct TapDetector : public Listener {

	Frame lastFrame;
	void onPolledFrame(const Controller & controller)
	{
		Frame thisFrame = controller.frame();
		int MaxHistory = 100;
		for (int i=1;i < MaxHistory; i++)
		{
			Frame frame = controller.frame(i-1);
			Frame previousFrame = controller.frame(i);
						
			//Last frame is invalid
			if (!previousFrame.isValid())
				break;
			
			//We reached the frame that was processed last time
			if (frame == lastFrame)
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
		}
		lastFrame = thisFrame;
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
};


int main(int argc, char * argv[])
{
	Controller controller;
	TapDetector tapDetector;
	
	controller.addListener(tapDetector);

	while (true)
	{
		tapDetector.onPolledFrame(controller);

		//Other application logic

		//Rendering 
	}
	
	return 0;
}