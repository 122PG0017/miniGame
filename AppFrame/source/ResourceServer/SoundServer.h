#pragma once
#include <string>
#include <unordered_map>
#include <tchar.h>
#include <string>

namespace AppFrame {
    class SoundServer {
    public:
        static void Initialize();
        static void Release();
        static void ClearSounds();
        static void CheckLoad();

        /**
        * \brief 読み込み済のファイルでなければmapに登録
        *
        * \param filename 読み込むファイル名
        * \return 読み込んだ値、読み込み済みなら-1を返す
        */
        static int LoadBGM(std::string filename) { return LoadSound(filename, _mapBGM, _bgmVolume); }
        static int Load3DBGM(std::string filename, float InitRadius, int ReverbNo) { return Load3DSound(filename, _map3DBGM, _bgmVolume, InitRadius, ReverbNo); }
        /**
        * \brief 読み込み済のファイルでなければmapに登録
        *
        * \param filename 読み込むファイル名
        * \return 読み込んだ値、読み込み済みなら-1を返す
        */
        static int LoadSE(std::string filename) { return LoadSound(filename, _mapSE, _seVolume); }
        static int Load3DSE(std::string filename, float InitRadius, int ReverbNo) { return Load3DSound(filename, _map3DSE, _bgmVolume, InitRadius, ReverbNo); }
        /**
        * \brief 読み込み済のファイルでなければmapに登録
        *
        * \param filename 読み込むファイル名
        * \return 読み込んだ値、読み込み済みなら-1を返す
        */
        static int LoadVoice(std::string filename) { return LoadSound(filename, _mapVoice, _voiceVolume); }
        static int Load3DVoice(std::string filename, float InitRadius, int ReverbNo) { return Load3DSound(filename, _map3DVoice, _bgmVolume, InitRadius, ReverbNo); }
        /**
        * \brief 読み込み済のファイルでなければmapに登録
        *
        * \param filename 読み込むファイル名
        * \return 読み込んだ値、読み込み済みなら-1を返す
        */
        static int LoadSoftSound(std::string filename);
        /**
         * \brief _mapGraphのキー検索
         *
         * \param filename 検索するキー名
         * \return キーに対応した値を返す
         */
        static int FindBGM(std::string filename) { return FindSound(filename, _mapBGM); }
        /**
        * \brief _mapBGMのキー検索
        *
        * \param filename 検索するキー名
        * \return キーに対応した値を返す
        */
        static int FindSE(std::string filename) { return FindSound(filename, _mapSE); }
        /**
        * \brief _mapVoiceのキー検索
        *
        * \param filename 検索するキー名
        * \return キーに対応した値を返す
        */
        static int FindVoice(std::string filename) { return FindSound(filename, _mapVoice); }

        static int EraseBGM(std::string filename) { return EraseSound(filename, _mapBGM); }
        static int EraseSE(std::string filename) { return EraseSound(filename, _mapSE); }
        static int EraseVoice(std::string filename) { return EraseSound(filename, _mapVoice); }


        /* \brief BGMのボリュームを設定する　(0.0f~1.0f 1.0は音声ファイル元々の音量)*/
        static void SetBGMVolume(float volume) { SetSoundVolume(volume, _bgmVolume, _mapBGM); }
        /* \brief SEのボリュームを設定する　(0.0f~1.0f 1.0は音声ファイル元々の音量)*/
        static void SetSEVolume(float volume) { SetSoundVolume(volume, _seVolume, _mapSE); }
        /* \brief ボイスのボリュームを設定する　(0.0f~1.0f 1.0は音声ファイル元々の音量)*/
        static void SetVoiceVolume(float volume) { SetSoundVolume(volume, _voiceVolume, _mapVoice); }

        static float GetBGMVolume() { return _bgmVolume; }
        static float GetSEVolume() { return _seVolume; }
        static float GetVoiceVolume() { return _voiceVolume; }

        static void StopBGM();
    private:
        static int FindSound(std::string filename, std::unordered_map<std::string, int>& map);
        static int EraseSound(std::string filename, std::unordered_map<std::string, int>& map);
        static int LoadSound(std::string filename, std::unordered_map<std::string, int>& map, float& volumeContainer);
        static int Load3DSound(std::string filename, std::unordered_map<std::string, int>& map, float& volumeContainer, float InitRadius = 256.0f, int ReverbNo = DX_REVERB_PRESET_DEFAULT);
        //音声ファイルのデフォルト音量の保存と設定ボリュームの適用
        static void InitializeSoundFile(int soundHandle, std::string filename, float volumeContainer);
        static void SetSoundVolume(float changeVolume, float& volumeContainer, std::unordered_map<std::string, int> map);


        static std::unordered_map<std::string, int> _mapBGM;
        static std::unordered_map<std::string, int> _map3DBGM;
        static std::unordered_map<std::string, int> _mapSE;
        static std::unordered_map<std::string, int> _map3DSE;
        static std::unordered_map<std::string, int> _mapVoice;
        static std::unordered_map<std::string, int> _map3DVoice;
        static std::unordered_map<std::string, int> _mapDefaultVolume;
        static std::unordered_map<std::string, int> _softHandle;
        struct ASyncSoundData {
            int soundHandle;
            std::string filename;
            float volumeContainer;
        };
        static std::vector<ASyncSoundData> _aSyncLoadingHandles;//非同期読み込み中のBGMデータ

        static float _bgmVolume;
        static float _seVolume;
        static float _voiceVolume;
    };
}