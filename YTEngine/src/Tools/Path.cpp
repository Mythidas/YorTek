#include "YTEngine/Tools/Path.h"
#include "YTEngine/Debug/Log.h"

#include <fstream>
#include <Windows.h>
#include <ShlObj.h>

namespace Yor
{
  namespace Utils
  {
    static std::vector<COMDLG_FILTERSPEC> getFilterSpec(const Yor::FileDialogFilters& filters)
    {
      // TODO: Add more specs filters
      std::vector<COMDLG_FILTERSPEC> specs;
      if (filters & FileDialogFilters::Project)
        specs.push_back({ L"Project Files (*.ytproj)", L"*.ytproj" });
      if (filters & FileDialogFilters::Scene)
        specs.push_back({ L"Scene Files (*.ytscene)", L"*.ytscene" });
      return specs;
    }
  }

  Path::Path(const char* path)
    : m_path(path)
  {
  }

  Path::Path(const std::string& path)
    : m_path(path)
  {
  }

  Path::Path(const FS::path& path)
    : m_path(path)
  {
  }

  std::string Path::readToString() const
  {
    if (!exists() || !isFile()) return std::string();

    std::ifstream stream(m_path.c_str());
    if (!stream.is_open()) return std::string();

    std::stringstream buf;
    buf << stream.rdbuf();
    stream.close();
    return buf.str();
  }

  void Path::write(const std::string& str) const
  {
    if (!isFile()) return;

    std::ofstream fout(m_path);
    if (fout.is_open())
    {
      fout << str;
      fout.close();
    }
    else
    {
      Log::error("Failed to create file! {0}", toString());
    }
  }

  bool Path::exists() const
  {
    return FS::exists(m_path);
  }

  bool Path::isFile() const
  {
    return !FS::is_directory(m_path);
  }

  Path Path::getDirectoryDialogBox()
  {
    // TODO Myth: Create a platform specific way to handle this operation
    FS::path path;
    HRESULT result = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(result))
    {
      IFileOpenDialog* pFileOpen;
      result = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
      if (SUCCEEDED(result))
      {
        result = pFileOpen->SetOptions(FOS_PICKFOLDERS);
        if (SUCCEEDED(result))
        {
          result = pFileOpen->Show(NULL);

          if (SUCCEEDED(result))
          {
            IShellItem* pItem;
            result = pFileOpen->GetResult(&pItem);
            if (SUCCEEDED(result))
            {
              PWSTR pszFilePath;
              result = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
              if (SUCCEEDED(result))
              {
                path = pszFilePath;
                CoTaskMemFree(pszFilePath);
              }
              pItem->Release();
            }
            pFileOpen->Release();
          }
          CoUninitialize();
        }
      }
    }

    return path;
  }

  Path Path::getFileOpenDialogBox(const FileDialogFilters& filters)
  {
    FS::path path;
    HRESULT result = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(result))
    {
      IFileOpenDialog* pFileOpen;
      result = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
      if (SUCCEEDED(result))
      {
        auto filterData = Utils::getFilterSpec(filters);
        result = pFileOpen->SetFileTypes(filterData.size(), filterData.data());
        if (SUCCEEDED(result))
        {
          result = pFileOpen->Show(NULL);

          if (SUCCEEDED(result))
          {
            IShellItem* pItem;
            result = pFileOpen->GetResult(&pItem);
            if (SUCCEEDED(result))
            {
              PWSTR pszFilePath;
              result = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
              if (SUCCEEDED(result))
              {
                path = pszFilePath;
                CoTaskMemFree(pszFilePath);
              }
              pItem->Release();
            }
            pFileOpen->Release();
          }
          CoUninitialize();
        }
      }
    }

    return path;
  }

  Path Path::getFileSaveDialogBox(const FileDialogFilters& filters)
  {
    FS::path path;
    HRESULT result = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(result))
    {
      IFileSaveDialog* pFileOpen;
      result = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileOpen));
      if (SUCCEEDED(result))
      {
        auto filterData = Utils::getFilterSpec(filters);
        result = pFileOpen->SetFileTypes(filterData.size(), filterData.data());
        if (SUCCEEDED(result))
        {
          result = pFileOpen->Show(NULL);
          if (SUCCEEDED(result))
          {
            IShellItem* pItem;
            result = pFileOpen->GetResult(&pItem);
            if (SUCCEEDED(result))
            {
              PWSTR pszFilePath;
              result = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
              if (SUCCEEDED(result))
              {
                UINT fileTypeIndex;
                result = pFileOpen->GetFileTypeIndex(&fileTypeIndex);
                if (SUCCEEDED(result))
                {
                  // TODO: This isn't intelligent and doesn't account for the user typing out the extension
                  path = pszFilePath;
                  std::wstring ext(filterData[fileTypeIndex - 1].pszSpec);
                  path += ext.substr(1);
                  CoTaskMemFree(pszFilePath);
                }

              }
              pItem->Release();
            }
            pFileOpen->Release();
          }
          CoUninitialize();
        }
      }
    }

    return path;
  }
}