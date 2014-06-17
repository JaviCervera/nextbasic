#include "bitmap.h"
#include "../core/string.h"
#include <wx/wx.h>
#include <string>

using namespace std;

extern "C" {

EXPORT void* CALL LoadBitmap(const char* filename) {
	// Set correct bitmap type based on extension
	string ext = Lower(ExtractExt(filename));
	wxBitmapType type = wxBITMAP_TYPE_INVALID;
	if ( ext == "bmp" )
		type = wxBITMAP_TYPE_BMP;
	else if ( ext == "ico" )
		type = wxBITMAP_TYPE_ICO;
	else if ( ext == "png" )
		type = wxBITMAP_TYPE_PNG;
	else if ( ext == "jpg"  ||  ext == "jpeg" )
		type = wxBITMAP_TYPE_JPEG;
	if ( type == wxBITMAP_TYPE_INVALID) return NULL;

	return new wxBitmap(filename, type);
}

EXPORT void CALL FreeBitmap(void* bitmap) {
	delete (wxBitmap*)bitmap;
}

}	// extern "C"