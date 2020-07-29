echo "Downloading glm..."
wget https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip >/dev/null 2>&1
unzip glm-0.9.9.8.zip >/dev/null 2>&1
mv glm/glm glmTemp
rm -rf glm glm-0.9.9.8.zip
mv glmTemp glm
