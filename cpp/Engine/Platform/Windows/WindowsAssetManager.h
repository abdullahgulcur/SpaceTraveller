#pragma once

namespace Engine{

    class WindowsAssetManager{
    private:
    public:

        WindowsAssetManager(){}
        ~WindowsAssetManager(){}

        template<typename T>
        void readBytesFromAsset(const char* filename, T& buffer) {

            std::ifstream file(filename, std::ios::binary);
            if (!file) throw std::runtime_error("Cannot open file!");

            file.seekg(0, std::ios::end);
            size_t size = file.tellg();
            file.seekg(0);

            buffer.resize(size);
            file.read(reinterpret_cast<char*>(buffer.data()), size);
        }
    };
}