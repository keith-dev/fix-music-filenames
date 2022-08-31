#include <memory>
#include <string>
#include <string_view>

class Scheme {
protected:
	std::string artist_, track_, name_;

public:
	Scheme(std::string_view track) :
		track_(track),
		name_("Track") {
	}
	Scheme(std::string_view artist, std::string_view track, std::string_view name) :
		artist_(artist),
		track_(track),
		name_(name) {
	}
	virtual ~Scheme() = default;
	virtual std::string_view name() const = 0;
	virtual std::string_view artist() const = 0;
	virtual std::string_view track() const = 0;

	static std::unique_ptr<Scheme> create(std::string_view name);
};

class StudioScheme : public Scheme {
public:
	StudioScheme(std::string_view artist, std::string_view track, std::string_view name) :
		Scheme(artist, track, name) {
	}
	std::string_view name() const override {
		return name_;
	}
	std::string_view artist() const override {
		return artist_;
	}
	std::string_view track() const override {
		return track_;
	}
};

class DefaultScheme : public Scheme {
public:
	DefaultScheme(std::string_view track) : Scheme(track) {
	}
	std::string_view name() const override {
		return "Track";
	}
	std::string_view artist() const override {
		return "Unknown Artist";
	}
	std::string_view track() const override {
		return "01";
	}
};
