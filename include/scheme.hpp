#pragma once

#include <memory>
#include <string>
#include <string_view>

//----------------------------------------------------------------------------
//
class Scheme {
private:
	std::string artist_, track_, name_;

public:
	Scheme(std::string_view artist, std::string_view track, std::string_view name) :
		artist_(artist), track_(track), name_(name) {
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

// found on recent online CD purchases
// artist - track. name
// Various Artists - 02. Life.mp3
class PurchasedStudioScheme : public Scheme {
public:
	PurchasedStudioScheme(std::string_view artist, std::string_view track, std::string_view name) :
		Scheme(artist, track, name) {
	}
	static std::unique_ptr<Scheme> create(std::string_view rootname);
};

// special spaceless fornat found on some Amazon purchased cds
// artist_-_track_-_name
// B00G7PONRI_(disc_1)_01_-_You_Ain't_Livin'.mp3
class SpacelessScheme : public Scheme {
public:
	SpacelessScheme(std::string_view track, std::string_view name) :
		Scheme({}, track, name) {
	}
	std::string_view artist() const override {
		return "Unknown Artist";
	}
	static std::unique_ptr<Scheme> create(std::string_view rootname);
};

// created by CD mastering, found on CDs going back to the 1980s to present
// artist - track - name
// Rufus with Chaka Khan - 04 - Music Man (The DJ Song).flac
class StudioScheme : public Scheme {
public:
	StudioScheme(std::string_view artist, std::string_view track, std::string_view name) :
		Scheme(artist, track, name) {
	}
	static std::unique_ptr<Scheme> create(std::string_view rootname);
};

// lazy: Track 01.mp3
class DefaultScheme : public Scheme {
public:
	DefaultScheme(std::string_view track) : Scheme({}, track, "Track") {
	}
	std::string_view artist() const override {
		return "Unknown Artist";
	}
	static std::unique_ptr<Scheme> create(std::string_view rootname);
};

#ifdef HIDE
// extended StudioScheme found on ClassicFM CDs
// conductor - orchestra - track - name
class ClassicFMScheme : public Scheme {
public:
	ClassicFMScheme(std::string_view artist, std::string_view track, std::string_view name) :
		Scheme(artist, track, name) {
	}
	static std::unique_ptr<Scheme> create(std::string_view rootname);
};

// created be abcde ripper
// track.name
class AbcdeScheme : public Scheme {
public:
	AbcdeScheme(std::string_view track, std::string_view name) :
		Scheme({}, track, name) {
	}
	std::string_view artist() const override {
		return "Unknown Artist";
	}
	static std::unique_ptr<Scheme> create(std::string_view rootname);
};

// created be abcde ripper
// track name
class GenericRipScheme : public Scheme {
public:
	GenericRipScheme(std::string_view track, std::string_view name) :
		Scheme({}, track, name) {
	}
	std::string_view artist() const override {
		return "Unknown Artist";
	}
	static std::unique_ptr<Scheme> create(std::string_view rootname);
};

// created be abcde ripper
// disk-track name
class MultiCdGenericRipScheme : public Scheme {
public:
	MultiCdGenericRipScheme(std::string_view track, std::string_view name) :
		Scheme({}, track, name) {
	}
	std::string_view artist() const override {
		return "Unknown Artist";
	}
	static std::unique_ptr<Scheme> create(std::string_view rootname);
};

// created be abcde ripper
// 1-07.Shes_strange.flac
class MultiCdGenericRipScheme2 : public Scheme {
public:
	MultiCdGenericRipScheme2(std::string_view track, std::string_view name) :
		Scheme({}, track, name) {
	}
	std::string_view artist() const override {
		return "Unknown Artist";
	}
	static std::unique_ptr<Scheme> create(std::string_view rootname);
};

// special spaceless fornati, source unknown, probably abcde
// Chic-08-Take_It_Off.flac
class SpacelessScheme2 : public Scheme {
public:
	SpacelessScheme2(std::string_view artist, std::string_view track, std::string_view name) :
		Scheme(artist, track, name) {
	}
	static std::unique_ptr<Scheme> create(std::string_view rootname);
};
#endif
