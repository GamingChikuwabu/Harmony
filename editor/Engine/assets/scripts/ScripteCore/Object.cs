using System.Diagnostics.Tracing;
using System.Runtime.CompilerServices;



namespace KALEIDOSCOPE
{
    public class Debug
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void PrintDebugLog(string msg);
    }

    public class Object
    {
        //=======================================================================
        //プロパティ
        //=======================================================================
        public string Name { get { return name; } set { name = value; } } // GameObjectの名前
        //=======================================================================
        //フィールド
        //=======================================================================
        [SerializeField] private string name = "";

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static Component AddComponent(Object gameobject,string componentname);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static Component GetComponent(Object gameobject, string componentname);
    }
}