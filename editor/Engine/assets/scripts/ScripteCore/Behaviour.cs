using System;
using Newtonsoft.Json;

namespace KALEIDOSCOPE
{
    public class Behaviour : Component
    {
        public bool IsEnable { get;set; }
        public Behaviour()
        {
            IsEnable = true;
        }
    }
}