#pragma once

#include <memory>
#include <string>
#include <string_view>

//------------------------------------------------------------------------------
//
class Scheme {
protected:
	std::string artist_, track_, name_;

public:
	Scheme(std::string_view artist, std::string_view track, std::string_view name) :
		artist_(artist),
		track_(track),
		name_(name) {
	}
	virtual ~Scheme() = default;
	virtual std::string_view name() const {
		return name_;
	}
	virtual std::string_view artist() const {
		return artist_;
	}
	virtual std::string_view track() const {
		return track_;
	}

	static std::unique_ptr<Scheme> create(std::string_view name);
};

class StudioScheme : public Scheme {
public:
	StudioScheme(std::string_view artist, std::string_view track, std::string_view name) :
		Scheme(artist, track, name) {
	}
};

class ClassicFMScheme : public Scheme {
public:
	ClassicFMScheme(std::string_view artist, std::string_view track, std::string_view name) :
		Scheme(artist, track, name) {
	}
};

class AbcdeScheme : public Scheme {
public:
	AbcdeScheme(std::string_view track, std::string_view name) :
		Scheme({}, track, name) {
	}
	std::string_view artist() const override {
		return "Unknown Artist";
	}
};

class DefaultScheme : public Scheme {
public:
	DefaultScheme(std::string_view track) : Scheme({}, track, "Track") {
	}
	std::string_view artist() const override {
		return "Unknown Artist";
	}
};
