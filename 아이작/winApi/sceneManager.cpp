#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

//�ε� ������ �Լ�
DWORD CALLBACK loadingThread(LPVOID prc)
{
	//��ü�� ���� �Լ��� ����
	sceneManager::_readyScene->init();

	//���� ���� ��ü�� ������ �ٲ۴�
	sceneManager::_currentScene = sceneManager::_readyScene;

	//�ε� �� ����
	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	return 0;
}

gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

HRESULT sceneManager::init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void sceneManager::release(void)
{
	//�� ��ü�� ���鼭 �����
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene)
			{
				miSceneList->second->release();
			}

			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}

		else
		{
			++miSceneList;
		}
	}
	_mSceneList.clear();
}

void sceneManager::update(void)
{
	//���� ���� �����Ѵٸ� ���� ���� ������Ʈ
	if (_currentScene) _currentScene->update();
}

void sceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}

//�� �߰�
gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	//���� ���ٸ� NULL ����
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));
	return scene;
}

//�ε��� �߰�
gameNode * sceneManager::addLoadingScene(string loadingSceneName, gameNode * scene)
{
	if (!scene) return NULL;

	_mLoadingSceneList.insert(make_pair(loadingSceneName, scene));
	return scene;
}

//�� ü����
HRESULT sceneManager::changeScene(string sceneName)
{
	//�ٲٷ��� �ϴ� ���� ã�´�
	mapSceneIter find = _mSceneList.find(sceneName);

	//�ٲ��� ���ϸ� E_FAIL ����
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ� �ϴ� ���� ������� ������ S_OK ����
	if (find->second == _currentScene) return S_OK;

	//���Ӱ� ����Ǵ� �� �ʱ�ȭ
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;

		return S_OK;
	}
	return E_FAIL;
}

