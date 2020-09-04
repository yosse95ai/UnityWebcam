using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;

public class test : MonoBehaviour
{
	[DllImport("UnityNativePluginTest")]
	private static extern void createCheckTexture(IntPtr data, int w, int h, int ch);

	private Texture2D texture_;
	private Color32[] pixels_;
	private GCHandle pixels_handle_;
	private IntPtr pixels_ptr_ = IntPtr.Zero;

	void Start()
	{
		// テクスチャを生成
		texture_ = new Texture2D(10, 10, TextureFormat.RGB24, false);
		// テクスチャの拡大方法をニアレストネイバーに変更
		texture_.filterMode = FilterMode.Point;
		// Color32 型の配列としてテクスチャの参照をもらう
		pixels_ = texture_.GetPixels32();
		// GC されないようにする
		pixels_handle_ = GCHandle.Alloc(pixels_, GCHandleType.Pinned);
		// そのテクスチャのアドレスをもらう
		pixels_ptr_ = pixels_handle_.AddrOfPinnedObject();
		// スクリプトがアタッチされたオブジェクトのテクスチャをコレにする
		GetComponent<Renderer>().material.mainTexture = texture_;
	}

	void Update()
	{
		// ネイティブ側でテクスチャを生成
		createCheckTexture(pixels_ptr_, texture_.width, texture_.height, 4);
		// セットして反映させる
		texture_.SetPixels32(pixels_);
		texture_.Apply();
	}

	void OnApplicationQuit()
	{
		// GC 対象にする
		pixels_handle_.Free();
	}
}
