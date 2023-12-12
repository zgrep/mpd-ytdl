#ifndef MPD_INPUT_YTDL_STREAM_HXX
#define MPD_INPUT_YTDL_STREAM_HXX

#include "../ProxyInputStream.hxx"
#include "lib/ytdl/Invoke.hxx"
#include "lib/ytdl/Init.hxx"

struct Tag;
class InputStreamHandler;

class YtdlInputStream final : public ProxyInputStream, public Ytdl::YtdlHandler {
	static const int MAX_RETRY = 1;

	std::unique_ptr<Ytdl::InvokeContext> context;
	std::unique_ptr<Tag> tag;
	std::exception_ptr pending_exception;
	const Ytdl::YtdlInit &init;

	int retry_counter = 0;

	void InvokeYtdl();

public:
	YtdlInputStream(const char *_uri, Mutex &_mutex, const Ytdl::YtdlInit &_init) noexcept;

	~YtdlInputStream() noexcept override;
	void Check() override;
	const char *GetURI() const noexcept override;

	std::unique_ptr<Tag> ReadTag() noexcept override;

	[[gnu::nonnull]]
	size_t Read(std::unique_lock<Mutex> &lock, void *ptr, size_t size) override;

	void OnComplete(Ytdl::YtdlMonitor* monitor) override;
	void OnError(Ytdl::YtdlMonitor* monitor, std::exception_ptr e) override;

	void OnInputStreamReady() noexcept override;
};

#endif
