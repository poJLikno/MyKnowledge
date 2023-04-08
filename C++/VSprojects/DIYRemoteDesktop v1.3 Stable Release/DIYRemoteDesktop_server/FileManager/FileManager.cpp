#include "FileManager.h"

int FileManager::GetEncoderClsid(const WCHAR *format, CLSID *pClsid)
{
    UINT  num = 0;          // number of image encoders
    UINT  size = 0;         // size of the image encoder array in bytes

    Gdiplus::ImageCodecInfo *pImageCodecInfo = NULL;

    Gdiplus::GetImageEncodersSize(&num, &size);
    if (size == 0)
        return -1;  // Failure

    pImageCodecInfo = (Gdiplus::ImageCodecInfo *)(malloc(size));
    if (pImageCodecInfo == NULL)
        return -1;  // Failure

    GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j)
    {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;  // Success
        }
    }

    free(pImageCodecInfo);
    return -1;  // Failure
}

void FileManager::HbitmapToJPEGImage(HBITMAP &bmp, const wchar_t *fileName, ULONG quality)
{
    // Create image from hBitmap
    Gdiplus::Image *image = Gdiplus::Bitmap::FromHBITMAP(bmp, NULL);

    // Get codec
    CLSID jpegClsid;
    GetEncoderClsid(L"image/jpeg", &jpegClsid);

    // Create image parametr
    Gdiplus::EncoderParameters prs = {};
    prs.Count = 1;
    prs.Parameter[0].Guid = Gdiplus::EncoderQuality;
    prs.Parameter[0].Type = Gdiplus::EncoderParameterValueTypeLong;
    prs.Parameter[0].NumberOfValues = 1;

    // Set image quality
    ULONG qual = quality;
    prs.Parameter[0].Value = &qual;

    // Save image
    image->Gdiplus::Image::Save(fileName, &jpegClsid, &prs);

    // Clean up
    delete image;
    image = nullptr;
}

size_t FileManager::GetFileSize(const char *filename)
{
    std::ifstream file;
    size_t fsize = 0;

    file.open(filename, std::ios_base::binary | std::ios_base::in);
    if (file.is_open())
    {
        file.seekg(0, std::ios_base::end);
        fsize = file.tellg();
    }
    else
    {
        file.close();
        throw std::runtime_error("Can't open file!\n");
    }

    file.close();

    return fsize;
}

void FileManager::WriteFile(const char *filename, char *data, size_t size)
{
    std::ofstream file;

    file.open(filename, std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);
    if (file.is_open())
    {
        file.write(data, size);
    }
    else
    {
        file.close();
        throw std::runtime_error("Can't open file!\n");
    }

    file.close();
}

void FileManager::ReadFile(const char *filename, char *buffer, size_t size)
{
    std::ifstream file;

    file.open(filename, std::ios_base::binary | std::ios_base::in);
    if (file.is_open())
    {
        file.read(buffer, size);
    }
    else
    {
        file.close();
        throw std::runtime_error("Can't open file!\n");
    }

    file.close();
}

void FileManager::SaveScreenshot(std::string &x, std::string &y, std::string &quality)
{
    HBITMAP screenShot = NULL;

    ImageManager::TakeScreenshot(screenShot, stoi(x), stoi(y));
    ImageManager::PinMouseCursor(screenShot);
    FileManager::HbitmapToJPEGImage(screenShot, L"image.jpg", (ULONG)stoi(quality));

    DeleteObject(screenShot);
}
