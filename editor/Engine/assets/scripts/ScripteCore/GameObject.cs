using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.Remoting.Messaging;
using System.Text;

namespace KALEIDOSCOPE
{
    public class GameObject : Object
    {
        //====================================================================================
        //変数
        //====================================================================================
        public Transform transform { get { return _transform; } set { _transform = value; } }
        [SerializeField] private Transform _transform;
        [SerializeField] private string tag = "";
        [SerializeField] private string layer = "";
       
        // 新しい GameObject を作成する静的メソッド
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static GameObject CreateGameObject(params Component[] components);

        // 新しい GameObject を作成する静的メソッド
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static GameObject CreateGameObject(Transform Transform);

        // 名前で GameObject を検索する静的メソッド
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static GameObject FindGameObject(string name);

        // 名前で GameObject を検索する静的メソッド
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static GameObject[] FindGameObjects(string name);

        // 名前で GameObject を検索する静的メソッド
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static GameObject Find(string name);

        // コンストラクタ
        public GameObject()
        {
            Debug.PrintDebugLog("test");
            Console.Write("test");
            transform = new Transform();
            AddComponent(transform);
        }

        // コンストラクタ
        public GameObject(Transform transform)
        {
            AddComponent(transform);
        }

        // 複数のコンポーネントを受け取るコンストラクタ
        public GameObject(params Component[] components)
        {
            // Transform コンポーネントの初期化
            transform = new Transform();
            AddComponent(transform);

            // 引数で渡されたコンポーネントを追加
            foreach (var component in components)
            {
                AddComponent(component);
            }
        }

        // コンポーネントを追加するメソッド
        public T AddComponent<T>(T component) where T : Component
        {
            string componentName = typeof(T).Name; // コンポーネントの型名を取得
            var cppcomponent = Object.AddComponent(this, componentName);
            cppcomponent.gameObject = this; // コンポーネントに親のGameObjectを設定
            return (T)cppcomponent;
        }

        // コンポーネントを文字列で追加
        public Component AddComponent(string componentName)
        {
            var cppcomponent = Object.AddComponent(this, componentName);
            cppcomponent.gameObject = this; // コンポーネントに親のGameObjectを設定
            return cppcomponent;
        }

        // コンポーネントを型で追加
        public T AddComponent<T>() where T : Component, new()
        {
            string componentName = typeof(T).Name; // コンポーネントの型名を取得
            var cppcomponent = Object.AddComponent(this, componentName);
            cppcomponent.gameObject = this; // コンポーネントに親のGameObjectを設定
            return (T)cppcomponent;
        }

        // 特定の型のコンポーネントを取得
        public T GetComponent<T>() where T : Component
        {
            string componentName = typeof(T).Name; // コンポーネントの型名を取得
            var cppcomponent = Object.GetComponent(this, componentName);
            if (cppcomponent != null)
                return cppcomponent as T;
            return null;
        }

        // 名前でコンポーネントを取得
        public Component GetComponent(string componentName)
        {
            var cppcomponent = Object.GetComponent(this, componentName);
            if( cppcomponent != null )
            {
                return cppcomponent;
            }
            return null;
        }
    }
}