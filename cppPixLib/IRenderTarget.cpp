#include "IRenderTarget.h"
#include "FilesystemRenderTarget.h"
#include "SDLRenderTarget.h"

using namespace Pix;

Pix::IRenderTargetPtr Pix::IRenderTarget::GetDefaultRenderer(const std::string& windowTitle, uint32_t width, uint32_t height)
{
#ifdef __arm__
		return IRenderTargetPtr(new FilesystemRenderTarget("/dev/spidev0.0"));
#else
		return IRenderTargetPtr(new SDLRenderTarget(windowTitle, width * 40, height * 40));
#endif
}
