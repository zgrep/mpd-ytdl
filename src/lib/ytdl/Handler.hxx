#ifndef MPD_LIB_YTDL_HANDLER_HXX
#define MPD_LIB_YTDL_HANDLER_HXX

#include "util/StringView.hxx"
#include "tag/Type.h"

namespace Ytdl {

class ParserContext;

enum class StringMetadataTag {
	CREATOR,
	EXTRACTOR,
	PLAYLIST_TITLE,
	TITLE,
	TYPE,
	URL,
	WEBPAGE_URL,
};

enum class IntMetadataTag {
	DURATION_MS,
	PLAYLIST_INDEX,
};

enum class ParseContinue {
	CONTINUE,
	CANCEL,
};

class MetadataHandler {
	friend class ParserContext;

	virtual ParseContinue OnEntryStart() noexcept = 0;
	virtual ParseContinue OnEntryEnd() noexcept = 0;
	virtual ParseContinue OnEnd() noexcept = 0;
	virtual ParseContinue OnMetadata(TagType tag, StringView value) noexcept = 0;
	virtual ParseContinue OnMetadata(StringMetadataTag tag, StringView value) noexcept = 0;
	virtual ParseContinue OnMetadata(IntMetadataTag tag, long long int value) noexcept = 0;
	virtual ParseContinue OnHeader(StringView header, StringView value) noexcept = 0;
};

} // namespace Ytdl

#endif
